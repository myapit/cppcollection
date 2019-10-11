apf=AP"$2".COM
tmpf="$2".com
apf1="$apf".test
nasm -w+all -O99 "$1" -o "$tmpf" -DBlankLength="$3"

cp -p "$tmpf" "$apf"
if true; then
  ./apacker-com < "$tmpf" > "$apf1"
  # 2>/dev/null
  if [ 0"`stat -c %s "$apf"`" -gt 0"`stat -c%s "$apf1"`" ]; then
    mv -f "$apf1" "$apf"
  fi
  rm -f "$apf1"
else
  echo "[sdl]
  windowresolution=16x16
  output=surface
  [render]
  frameskip=99
  scaler=none
  aspect=false
  [cpu]
  cycles=1000000
  [mixer]
  nosound=true
  [autoexec]
  mount c .
  c:
  apack ""$tmpf"" ""$apf""
  exit" > "$2".conf.tmp
  DISPLAY=:91 dosbox -conf "$2".conf.tmp
  rm -f "$2".conf.tmp
fi

if [ 0"`stat -c %s "$tmpf"`" -gt 0"`stat -c%s "$apf"`" ]; then
  mv -f "$apf" "$tmpf"
fi

upx-nrv --best --ultra-brute "$tmpf" &> /dev/null
upx-ucl --best --ultra-brute "$tmpf" &> /dev/null
upx     --best --ultra-brute "$tmpf" &> /dev/null
rm -f "$2".{001,001,002,upx}
