while true; do
  make -s && ./main &
	PID=$!
	inotifywait -e modify *.h *.cpp
	kill $PID
done

