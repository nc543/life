# Berkeley Packet Filter

BPF (classic BPF, cBPF) 原本只用來過濾網路封包，現在改用 eBPF (extended Berkeley
Packet Filter)，新增一些功能及改善效能，可以用在非網路部份而從網路子系統移到自己的 kernel/bpf 目錄。

eBPF 在 Linux 3.18+ 新增系統呼叫 bpf() 進行相關操作，以及一個函式庫包裝這些操作。
eBPF 擴充 cBPF 功能，包括透過 BPF_CALL opcode 呼叫 a fixed set of kernel 內部 helper 函數、存取共享資料結構如 eBPF maps、等。

cBPF 執行前會轉換成 eBPF。Kernel 載入 cBPF 或 eBPF 程式前會先分析，確保不會危害運作的系統。

## eBPF 設計及 Architecture
eBPF map 是任何資料型態的 key 跟 value 對應，一般視為 binary blobs，
建立時只需要指定 key 及 value 的大小。

       A  user  process  can  create multiple maps (with key/value-pairs being
       opaque bytes of data) and access them via file descriptors.   Different
       eBPF  programs  can  access  the same maps in parallel.  It's up to the
       user process and eBPF program to decide what they store inside maps.

       There's one special map type, called a program array.  This type of map
       stores  file  descriptors  referring  to  other  eBPF programs.  When a
       lookup in the map is performed, the program flow is redirected in-place
       to  the  beginning  of another eBPF program and does not return back to
       the calling program.  The level of nesting has a fixed limit of 32,  so
       that  infinite  loops  cannot be crafted.  At runtime, the program file
       descriptors stored in the map can be modified, so program functionality
       can  be  altered based on specific requirements.  All programs referred
       to in a program-array map must have been  previously  loaded  into  the
       kernel via bpf().  If a map lookup fails, the current program continues
       its execution.  See BPF_MAP_TYPE_PROG_ARRAY below for further details.

一般來說，eBPF 程式由使用者行程載入，當行程結束時自動 unload。
       但有些情況，例如 tc-bpf(8)，即使載入的行程結束程式仍會持續執行，tc 子系統
       holds a reference to the eBPF program after the file descrip‐
       tor  has  been  closed by the user-space program.  Thus, whether a spe‐
       cific program continues to live inside the kernel depends on how it  is
       further  attached  to  a given kernel subsystem after it was loaded via
       bpf().

每個 eBPF 程式是一群可以安全執行到完成的指令。
       An in-kernel verifier statically determines that the
       eBPF program terminates and is safe to execute.   During  verification,
       the  kernel  increments  reference counts for each of the maps that the
       eBPF program uses, so that the attached maps can't be removed until the
       program is unloaded.

eBPF 程式可依附到不同事件來驅動，這些事件可以是網路封包到來、tracing 事件、
網路 queueing disciplines (依附到 tc
classifier) 的 classification 事件、以及未來其它可能的新增。
eBPF 程式可以儲存資訊到 map、呼叫 a fixed set of kernel 內部 helper 函數。

一個 eBPF 程式可以依附到多個事件，不同的 eBPF 程式可以存取同一個 map：
```
tracing     tracing    tracing    packet      packet     packet
event A     event B    event C    on eth0     on eth1    on eth2
 |             |         |          |           |          ^
 |             |         |          |           v          |
 --> tracing <--     tracing      socket    tc ingress   tc egress
      prog_1          prog_2      prog_3    classifier    action
      |  |              |           |         prog_4      prog_5
   |---  -----|  |------|          map_3        |           |
 map_1       map_2                              --| map_4 |--
```

## bpf()

```
#include <linux/bpf.h>

int bpf(int cmd, union bpf_attr *attr, unsigned int size);
```


##

eBPF 直譯器和 JIT 編譯器
衍生自 BPF，在使用者層級進行資料過濾和分析之後「再通知」核心
後來引入 BPF 提出的 bytecode，於是經由特製的工具，將原本執行在使用者層級的程式碼轉變成 bytecode，然後「注入」到運作於核心的 eBPF 虛擬機器去執行，省去可觀的 context switch 和資料交換成本。

##

### 引數
bpf() 做什麼動作由引數 cmd 決定，伴隨指向 union bpf_attr 的引數 attr 跟大小 size。

cmd 值：
* BPF_MAP_CREATE：建立一個 map 並回傳 map 的檔案描述子。
* BPF_MAP_LOOKUP_ELEM：Look up an element by key in a  specified  map  並回其值。
* BPF_MAP_UPDATE_ELEM：建立或更新 an element (key/value pair) in a specified map.
* BPF_MAP_DELETE_ELEM：Look up and delete an element by key in a specified map.
* BPF_MAP_GET_NEXT_KEY：Look  up an element by key in a specified map and return the key of the next element.
* BPF_PROG_LOAD：驗證並載入 eBPF 程式，回傳程式的檔案描述子。

union bpf_attr 包含 various anonymous structures，由不同的 cmd 使用

```
union bpf_attr {
    struct {    /* Used by BPF_MAP_CREATE */
        __u32         map_type;
        __u32         key_size;    /* size of key in bytes */
        __u32         value_size;  /* size of value in bytes */
        __u32         max_entries; /* maximum number of entries
                                      in a map */
    };

    struct {    /* Used by BPF_MAP_*_ELEM and BPF_MAP_GET_NEXT_KEY
                   commands */
        __u32         map_fd;
        __aligned_u64 key;
        union {
            __aligned_u64 value;
            __aligned_u64 next_key;
        };
        __u64         flags;
    };

    struct {    /* Used by BPF_PROG_LOAD */
        __u32         prog_type;
        __u32         insn_cnt;
        __aligned_u64 insns;      /* 'const struct bpf_insn *' */
        __aligned_u64 license;    /* 'const char *' */
        __u32         log_level;  /* verbosity level of verifier */
        __u32         log_size;   /* size of user buffer */
        __aligned_u64 log_buf;    /* user supplied 'char *'
                                     buffer */
        __u32         kern_version;
                                  /* checked when prog_type=kprobe
                                     (since Linux 4.1) */
    };
} __attribute__((aligned(8)));
```

### eBPF maps
       Maps are a generic data structure for storage  of  different  types  of
       data.   They  allow  sharing  of data between eBPF kernel programs, and
       also between kernel and user-space applications.

       Each map type has the following attributes:

       *  type
       *  maximum number of elements
       *  key size in bytes
       *  value size in bytes

       The following wrapper functions demonstrate how various bpf()  commands
       can  be used to access the maps.  The functions use the cmd argument to
       invoke different operations.

       BPF_MAP_CREATE
              The BPF_MAP_CREATE command creates a new map,  returning  a  new
              file descriptor that refers to the map.

                  int
                  bpf_create_map(enum bpf_map_type map_type,
                                 unsigned int key_size,
                                 unsigned int value_size,
                                 unsigned int max_entries)
                  {
                      union bpf_attr attr = {
                          .map_type    = map_type,
                          .key_size    = key_size,
                          .value_size  = value_size,
                          .max_entries = max_entries
                      };

                      return bpf(BPF_MAP_CREATE, &attr, sizeof(attr));
                  }

              The  new  map has the type specified by map_type, and attributes
              as specified in key_size, value_size, and max_entries.  On  suc‐
              cess, this operation returns a file descriptor.  On error, -1 is
              returned and errno is set to EINVAL, EPERM, or ENOMEM.

              The key_size and value_size attributes will be used by the veri‐
              fier during program loading to check that the program is calling
              bpf_map_*_elem() helper functions with a  correctly  initialized
              key and to check that the program doesn't access the map element
              value beyond the specified value_size.  For example, when a  map
              is created with a key_size of 8 and the eBPF program calls

                  bpf_map_lookup_elem(map_fd, fp - 4)

              the  program  will be rejected, since the in-kernel helper func‐
              tion

                  bpf_map_lookup_elem(map_fd, void *key)

              expects to read 8 bytes from the location pointed to by key, but
              the  fp - 4  (where fp is the top of the stack) starting address
              will cause out-of-bounds stack access.

              Similarly, when a map is created with a value_size of 1 and  the
              eBPF program contains

                  value = bpf_map_lookup_elem(...);
                  *(u32 *) value = 1;

              the  program  will  be  rejected,  since  it  accesses the value
              pointer beyond the specified 1 byte value_size limit.

              Currently, the following values are supported for map_type:

                  enum bpf_map_type {
                      BPF_MAP_TYPE_UNSPEC,  /* Reserve 0 as invalid map type */
                      BPF_MAP_TYPE_HASH,
                      BPF_MAP_TYPE_ARRAY,
                      BPF_MAP_TYPE_PROG_ARRAY,
                  };

              map_type selects one of the available map implementations in the
              kernel.   For  all map types, eBPF programs access maps with the
              same  bpf_map_lookup_elem()  and  bpf_map_update_elem()   helper
              functions.   Further  details of the various map types are given
              below.

       BPF_MAP_LOOKUP_ELEM
              The BPF_MAP_LOOKUP_ELEM command looks up an element with a given
              key in the map referred to by the file descriptor fd.

                  int
                  bpf_lookup_elem(int fd, const void *key, void *value)
                  {
                      union bpf_attr attr = {
                          .map_fd = fd,
                          .key    = ptr_to_u64(key),
                          .value  = ptr_to_u64(value),
                      };

                      return bpf(BPF_MAP_LOOKUP_ELEM, &attr, sizeof(attr));
                  }

              If  an  element  is found, the operation returns zero and stores
              the element's value into value, which must point to a buffer  of
              value_size bytes.

              If  no element is found, the operation returns -1 and sets errno
              to ENOENT.

       BPF_MAP_UPDATE_ELEM
              The BPF_MAP_UPDATE_ELEM command creates or  updates  an  element
              with  a  given  key/value  in  the  map  referred to by the file
              descriptor fd.

                  int
                  bpf_update_elem(int fd, const void *key, const void *value,
                                  uint64_t flags)
                  {
                      union bpf_attr attr = {
                          .map_fd = fd,
                          .key    = ptr_to_u64(key),
                          .value  = ptr_to_u64(value),
                          .flags  = flags,
                      };

                      return bpf(BPF_MAP_UPDATE_ELEM, &attr, sizeof(attr));
                  }

              The flags argument should be specified as one of the following:

              BPF_ANY
                     Create a new element or update an existing element.

              BPF_NOEXIST
                     Create a new element only if it did not exist.

              BPF_EXIST
                     Update an existing element.

              On success,  the  operation  returns  zero.   On  error,  -1  is
              returned  and  errno  is set to EINVAL, EPERM, ENOMEM, or E2BIG.
              E2BIG indicates that the number of elements in the  map  reached
              the  max_entries  limit  specified at map creation time.  EEXIST
              will be returned if flags specifies BPF_NOEXIST and the  element
              with  key already exists in the map.  ENOENT will be returned if
              flags specifies BPF_EXIST and the element with key doesn't exist
              in the map.

       BPF_MAP_DELETE_ELEM
              The BPF_MAP_DELETE_ELEM command deleted the element whose key is
              key from the map referred to by the file descriptor fd.

                  int
                  bpf_delete_elem(int fd, const void *key)
                  {
                      union bpf_attr attr = {
                          .map_fd = fd,
                          .key    = ptr_to_u64(key),
                      };

                      return bpf(BPF_MAP_DELETE_ELEM, &attr, sizeof(attr));
                  }

              On success, zero is returned.  If the element is not  found,  -1
              is returned and errno is set to ENOENT.

       BPF_MAP_GET_NEXT_KEY
              The  BPF_MAP_GET_NEXT_KEY  command looks up an element by key in
              the map referred to by the  file  descriptor  fd  and  sets  the
              next_key pointer to the key of the next element.

                  int
                  bpf_get_next_key(int fd, const void *key, void *next_key)
                  {
                      union bpf_attr attr = {
                          .map_fd   = fd,
                          .key      = ptr_to_u64(key),
                          .next_key = ptr_to_u64(next_key),
                      };

                      return bpf(BPF_MAP_GET_NEXT_KEY, &attr, sizeof(attr));
                  }

              If  key  is  found,  the  operation  returns  zero  and sets the
              next_key pointer to the key of the next element.  If key is  not
              found,  the operation returns zero and sets the next_key pointer
              to the key of the first element.  If key is the last element, -1
              is  returned  and  errno is set to ENOENT.  Other possible errno
              values are ENOMEM, EFAULT, EPERM, and EINVAL.  This  method  can
              be used to iterate over all elements in the map.

       close(map_fd)
              Delete  the map referred to by the file descriptor map_fd.  When
              the user-space program that created a map exits, all  maps  will
              be deleted automatically (but see NOTES).

### eBPF map types
       The following map types are supported:

       BPF_MAP_TYPE_HASH
              Hash-table maps have the following characteristics:

              *  Maps  are created and destroyed by user-space programs.  Both
                 user-space and eBPF programs can perform lookup, update,  and
                 delete operations.

              *  The  kernel  takes  care  of allocating and freeing key/value
                 pairs.

              *  The map_update_elem() helper with fail to insert new  element
                 when  the  max_entries  limit is reached.  (This ensures that
                 eBPF programs cannot exhaust memory.)

              *  map_update_elem() replaces existing elements atomically.

              Hash-table maps are optimized for speed of lookup.

       BPF_MAP_TYPE_ARRAY
              Array maps have the following characteristics:

              *  Optimized for fastest possible lookup.   In  the  future  the
                 verifier/JIT  compiler may recognize lookup() operations that
                 employ a constant key and optimize it into constant  pointer.
                 It  is  possible  to  optimize a non-constant key into direct
                 pointer arithmetic as well, since pointers and value_size are
                 constant  for  the life of the eBPF program.  In other words,
                 array_map_lookup_elem() may be 'inlined' by the  verifier/JIT
                 compiler  while preserving concurrent access to this map from
                 user space.

              *  All array elements pre-allocated and zero initialized at init
                 time

              *  The key is an array index, and must be exactly four bytes.

              *  map_delete_elem() fails with the error EINVAL, since elements
                 cannot be deleted.

              *  map_update_elem() replaces elements in a  nonatomic  fashion;
                 for  atomic updates, a hash-table map should be used instead.
                 There is however one special case that can also be used  with
                 arrays:  the  atomic  built-in  __sync_fetch_and_add() can be
                 used on 32 and 64 bit atomic counters.  For example,  it  can
                 be  applied on the whole value itself if it represents a sin‐
                 gle counter, or in case of a  structure  containing  multiple
                 counters,  it  could be used on individual counters.  This is
                 quite often useful for aggregation and accounting of events.

              Among the uses for array maps are the following:

              *  As "global" eBPF variables: an array of 1 element  whose  key
                 is  (index) 0 and where the value is a collection of 'global'
                 variables which eBPF programs can use to keep  state  between
                 events.

              *  Aggregation of tracing events into a fixed set of buckets.

              *  Accounting of networking events, for example, number of pack‐
                 ets and packet sizes.

       BPF_MAP_TYPE_PROG_ARRAY (since Linux 4.2)
              A program array map is a special kind of  array  map  whose  map
              values  contain  only  file  descriptors referring to other eBPF
              programs.  Thus,  both  the  key_size  and  value_size  must  be
              exactly  four  bytes.   This map is used in conjunction with the
              bpf_tail_call() helper.

              This means that  an  eBPF  program  with  a  program  array  map
              attached to it can call from kernel side into

                  void bpf_tail_call(void *context, void *prog_map, unsigned int index);

              and therefore replace its own program flow with the one from the
              program at the given program array slot, if present.   This  can
              be regarded as kind of a jump table to a different eBPF program.
              The invoked program will then reuse the same stack.  When a jump
              into  the new program has been performed, it won't return to the
              old program anymore.

              If no eBPF program is found at the given index  of  the  program
              array (because the map slot doesn't contain a valid program file
              descriptor, the specified lookup index/key is out of bounds,  or
              the limit of 32 nested calls has been exceed), execution contin‐
              ues with the current eBPF program.  This can be used as a  fall-
              through for default cases.

              A  program  array map is useful, for example, in tracing or net‐
              working, to handle individual system calls or protocols in their
              own  subprograms  and use their identifiers as an individual map
              index.  This approach may result in  performance  benefits,  and
              also makes it possible to overcome the maximum instruction limit
              of a single eBPF program.  In dynamic environments, a user-space
              daemon  might  atomically replace individual subprograms at run-
              time with newer versions to alter overall program behavior,  for
              instance, if global policies change.

### eBPF programs
       The BPF_PROG_LOAD command is used to load an eBPF program into the ker‐
       nel.  The return value for this command is a new file descriptor  asso‐
       ciated with this eBPF program.

           char bpf_log_buf[LOG_BUF_SIZE];

           int
           bpf_prog_load(enum bpf_prog_type type,
                         const struct bpf_insn *insns, int insn_cnt,
                         const char *license)
           {
               union bpf_attr attr = {
                   .prog_type = type,
                   .insns     = ptr_to_u64(insns),
                   .insn_cnt  = insn_cnt,
                   .license   = ptr_to_u64(license),
                   .log_buf   = ptr_to_u64(bpf_log_buf),
                   .log_size  = LOG_BUF_SIZE,
                   .log_level = 1,
               };

               return bpf(BPF_PROG_LOAD, &attr, sizeof(attr));
           }

       prog_type is one of the available program types:

           enum bpf_prog_type {
               BPF_PROG_TYPE_UNSPEC,        /* Reserve 0 as invalid
                                               program type */
               BPF_PROG_TYPE_SOCKET_FILTER,
               BPF_PROG_TYPE_KPROBE,
               BPF_PROG_TYPE_SCHED_CLS,
               BPF_PROG_TYPE_SCHED_ACT,
           };

       For further details of eBPF program types, see below.

       The remaining fields of bpf_attr are set as follows:

       *  insns is an array of struct bpf_insn instructions.

       *  insn_cnt is the number of instructions in the program referred to by
          insns.

       *  license 是 license 字串，呼叫 gpl_only helper 函數必須是 GPL 相容的。
          licensing 規則跟 kernel 模組一樣，可以使用
          dual licenses，例如 "Dual BSD/GPL"。

       *  log_buf  is  a pointer to a caller-allocated buffer in which the in-
          kernel verifier can store the  verification  log.   This  log  is  a
          multi-line string that can be checked by the program author in order
          to understand how the verifier came to the conclusion that the  eBPF
          program  is unsafe.  The format of the output can change at any time
          as the verifier evolves.

       *  log_size size of the buffer pointed to by log_bug.  If the  size  of
          the buffer is not large enough to store all verifier messages, -1 is
          returned and errno is set to ENOSPC.

       *  log_level verbosity level of the verifier.  A value  of  zero  means
          that the verifier will not provide a log; in this case, log_buf must
          be a NULL pointer, and log_size must be zero.

       Applying close(2) to the file descriptor returned by BPF_PROG_LOAD will
       unload the eBPF program (but see NOTES).

       Maps  are  accessible  from eBPF programs and are used to exchange data
       between eBPF programs and between eBPF  programs  and  user-space  pro‐
       grams.   For  example,  eBPF  programs can process various events (like
       kprobe, packets) and store their data into a map, and  user-space  pro‐
       grams  can  then  fetch data from the map.  Conversely, user-space pro‐
       grams can use a map as a configuration mechanism,  populating  the  map
       with values checked by the eBPF program, which then modifies its behav‐
       ior on the fly according to those values.

### eBPF program types
       eBPF program type (prog_type) 決定可呼叫的 kernel helper 函數子集及
       the program input (context)—the format of struct bpf_context
       (which is the data blob passed into the eBPF program as the first argu‐
       ment).

       For example, a tracing program does not have the exact same  subset  of
       helper  functions as a socket filter program (though they may have some
       helpers in common).  Similarly, the input (context) for a tracing  pro‐
       gram  is  a  set  of register values, while for a socket filter it is a
       network packet.

       The set of functions available to eBPF programs of  a  given  type  may
       increase in the future.

       The following program types are supported:

       BPF_PROG_TYPE_SOCKET_FILTER (since Linux 3.19)
              Currently,  the set of functions for BPF_PROG_TYPE_SOCKET_FILTER
              is:

                  bpf_map_lookup_elem(map_fd, void *key)
                                      /* look up key in a map_fd */
                  bpf_map_update_elem(map_fd, void *key, void *value)
                                      /* update key/value */
                  bpf_map_delete_elem(map_fd, void *key)
                                      /* delete key in a map_fd */

              The bpf_context argument is a pointer to a struct __sk_buff.

       BPF_PROG_TYPE_KPROBE (since Linux 4.1)
              [To be documented]

       BPF_PROG_TYPE_SCHED_CLS (since Linux 4.1)
              [To be documented]

       BPF_PROG_TYPE_SCHED_ACT (since Linux 4.1)
              [To be documented]

### Events
程式載入後可以依附某個事件來執行，不同 kernel 子系統有不同作法。

依附 eBPF 程式 prog_fd 到 socket sockfd (Linux 3.19+)
```
setsockopt(sockfd, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd, sizeof(prog_fd));
```

依附 eBPF 程式 prog_fd 到 perf_event_open() 產生的 perf event 檔案描述子
event_fd (Linux 4.1+)
```
ioctl(event_fd, PERF_EVENT_IOC_SET_BPF, prog_fd);
```

## EXAMPLES
```
/* bpf+sockets example:
 * 1. create array map of 256 elements
 * 2. load program that counts number of packets received
 *    r0 = skb->data[ETH_HLEN + offsetof(struct iphdr, protocol)]
 *    map[r0]++
 * 3. attach prog_fd to raw socket via setsockopt()
 * 4. print number of received TCP/UDP packets every second
 */
int
main(int argc, char **argv)
{
    int sock, map_fd, prog_fd, key;
    long long value = 0, tcp_cnt, udp_cnt;

    map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, sizeof(key),
                            sizeof(value), 256);
    if (map_fd < 0) {
        printf("failed to create map '%s'\n", strerror(errno));
        /* likely not run as root */
        return 1;
    }

    struct bpf_insn prog[] = {
        BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),        /* r6 = r1 */
        BPF_LD_ABS(BPF_B, ETH_HLEN + offsetof(struct iphdr, protocol)),
                                /* r0 = ip->proto */
        BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_0, -4),
                                /* *(u32 *)(fp - 4) = r0 */
        BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),       /* r2 = fp */
        BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4),      /* r2 = r2 - 4 */
        BPF_LD_MAP_FD(BPF_REG_1, map_fd),           /* r1 = map_fd */
        BPF_CALL_FUNC(BPF_FUNC_map_lookup_elem),
                                /* r0 = map_lookup(r1, r2) */
        BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2),
                                /* if (r0 == 0) goto pc+2 */
        BPF_MOV64_IMM(BPF_REG_1, 1),                /* r1 = 1 */
        BPF_XADD(BPF_DW, BPF_REG_0, BPF_REG_1, 0, 0),
                                /* lock *(u64 *) r0 += r1 */
        BPF_MOV64_IMM(BPF_REG_0, 0),                /* r0 = 0 */
        BPF_EXIT_INSN(),                            /* return r0 */
    };

    prog_fd = bpf_prog_load(BPF_PROG_TYPE_SOCKET_FILTER, prog,
                            sizeof(prog), "GPL");

    sock = open_raw_sock("lo");

    assert(setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd,
                      sizeof(prog_fd)) == 0);

    for (;;) {
        key = IPPROTO_TCP;
        assert(bpf_lookup_elem(map_fd, &key, &tcp_cnt) == 0);
        key = IPPROTO_UDP
        assert(bpf_lookup_elem(map_fd, &key, &udp_cnt) == 0);
        printf("TCP %lld UDP %lld packets0, tcp_cnt, udp_cnt);
        sleep(1);
    }

    return 0;
}
```

在 kernel 原始碼 samples/bpf 目錄有一些完整可用的程式碼範例。

## 回傳值
成功的話，BPF_MAP_CREATE 跟 BPF_PROG_LOAD 回傳 associated 的 file descriptor，其它回傳 0。

錯誤回傳 -1，並設定 errno
* EPERM：缺 CAP_SYS_ADMIN 權限。所有 bpf() 指令需要 CAP_SYS_ADMIN 權限。
* ENOMEM：記憶體不足
* EBADF：fd 不是開啟的 file descriptor
* EFAULT：key、value、log_buf、或 insns 超出可存取的位址空間
* EINVAL：cmd 不認得
* EINVAL (BPF_MAP_CREATE)：map_type 或 attributes 無效
* EINVAL (BPF_MAP_*_ELEM)：部份沒用的 union bpf_attr 欄位沒設為 0
* EINVAL (BPF_PROG_LOAD)：嘗試載入 invalid 程式，由於指令不認得、使用保留的欄位、跳出範圍、無限迴圈、或呼叫未知的函數。
* EACCES (BPF_PROG_LOAD)：程式不安全，可能因為存取不允許的記憶體區域或未初始化的堆疊/暫存器、函數限制跟實際類型不符合、或存取未對齊的記憶體。建議用 log_level = 1 呼叫 bpf() 看 log_buf 來查驗驗證器提供的特定原因。
* ENOENT (BPF_MAP_LOOKUP_ELEM 或 BPF_MAP_DELETE_ELEM)：找不到所給的 key。
* E2BIG：程式太大或 map 達到 max_entries 限制。

## NOTES

eBPF 物件 (maps 及 programs) 可透過其檔案描述子在行程間共用，例如透過 fork()
繼承的 eBPF 檔案描述子，透過 UNIX domain socket transferred，如同一般情況用
dup() 類的呼叫來複製。

當所有 refer to 某一 eBPF 物件的檔案描述子都關閉了才會解除配置物件。

eBPF 程式可用受限的 C 語言來寫，然後用 clang 編譯成 bytecode。這個受限的 C
沒有迴圈、全域變數、variadic 函數、浮點數字、及傳遞 struct 給函數。在 Linux
原始碼 samples/bpf/*_kern.c 有一些例子。

kernel 內含有 JIT 編譯器，將 eBPF bytecode 轉成原生機器碼以得到較好的效能。JIT
編譯器預設是關閉的，可以透過寫整數字串到 `/proc/sys/net/core/bpf_jit_enable` 設定:
* 0：關閉 JIT 編譯 (預設).
* 1：常態編譯
* 2：除錯模式，產生的 opcode 以十六進位數字 dumped 到 kernel log，可用 kernel 原始碼的 tools/net/bpf_jit_disasm.c 來進行反組譯。

目前 x86-64、arm64、及 s390 有 eBPF JIT 編譯器。

## 參考來源及延伸閱讀
* [Extending extended BPF](https://lwn.net/Articles/603983/)
* man bpf
* [kernel Documentation/networking/filter.txt](https://www.kernel.org/doc/Documentation/networking/filter.txt)：說明 classic 及 extended BPF
* seccomp(2), socket(7), tc(8), tc-bpf(8)
* [tcpdump](http://lirobo.blogspot.tw/2014/11/tcpdump.html)
* [packet socket](http://lirobo.blogspot.tw/2014/12/packet-socket.html)
* [rbpf](https://github.com/qmonnet/rbpf) 以 Rust 程式語言實作 eBPF 的虛擬機器
* ftrace 擷取核心資訊
