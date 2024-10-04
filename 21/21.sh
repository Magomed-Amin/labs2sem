 if [[ $1 = "?" ]]; then
  echo "Usage:"
  echo "  ./$(basename -- "$0") <maximum file size (bytes)> <suffix> [output file name] [keys]"
  echo $'\nParams:\n  output file name - default: "out.[introduced suffix]"\n'
  echo $'\nKeys:\n  -i    Show information about the progress of the merger'
  echo $'  -d    Delete source files'
  exit 0
fi

out="out.$2"
if ! [[ "-i -d" =~ $3 || -z $3 ]]; then
  out="$3"
fi

ok=0
for name in "$(dirname "$0")"/*
do
  if [[ -f $name ]]; then
    if [[ $(stat -c %s "$name") -lt $1 && "${name##*.}" = "$2" ]]; then
      cat "$name" >> "$out"
      if [[ ok -eq 0 ]]; then ok=1; fi

      if [[ $@ =~ "-i" ]]; then
        echo "INFO: file <$(basename -- "$name")> (size: $(stat -c %s "$name") b) insert to <$out>"
      fi

      if [[ $@ =~ "-d" ]]; then
        rm "$name"
      fi
    fi
  fi
done

if [[ ok -eq 1 ]]; then
  echo "INFO: completed"
else
  echo "INFO: such files not found"
fi
