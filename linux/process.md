
In a POSIX-conformant operating system,

process group (行程群組)：a collection of 一個或以上的行程。給行程群組的 signal 會送給群組中每個行程。

session：a collection of 一個或以上的行程群組. A process group is not permitted to migrate from one session to another, and a process may not create a process group that belongs to another session; furthermore, a process is not permitted to join a process group that is a member of another session—that is, a process is not permitted to migrate from one session to another.

When a process replaces its image with a new image (by calling one of the exec functions), the new image is subjected to the same process group (and thus session) membership as the old image.
