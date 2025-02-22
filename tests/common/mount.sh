skip_unless test "$SUDO"
skip_if test "$UNAME" = "Darwin"

clean_scratch
mkdir scratch/{foo,mnt}
sudo mount -t tmpfs tmpfs scratch/mnt
"$XTOUCH" scratch/foo/bar scratch/mnt/baz

bfs_diff scratch -mount
ret=$?

sudo umount scratch/mnt
return $ret
