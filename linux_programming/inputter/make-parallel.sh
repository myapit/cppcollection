prog="$1"
out="$2"
lock="$2".lock
rm -f "$out"
#xvfb-run -n91 -s '-screen 0 80x80x8' xclock&
#xpid=$!
if test -f "$prog" ; then
  #for s in 0 `seq 300 700`;do
  for s in `seq 0 19`;do
  #for s in 0 1 2 4 7 8 9 41; do
    ( temp="PM$s"
      ./make.sh $prog $temp $s
      flock 91
      if [ ! -f $out \
             -o 0"`stat -c %s $out`" \
            -ge 0"`stat -c %s $temp".com"`" ]; then
        mv -f $temp".com" $out
        echo "`stat -c %s $out` bytes with -DBlankLength=$s"
      else
        rm -f $temp".com"
      fi )
      # 91> $lock &
    #while [ `jobs -p | wc -l` -ge 4 ]; do sleep 0.05; done
  done
  wait
  rm -f $lock
fi
#kill $xpid
wait
