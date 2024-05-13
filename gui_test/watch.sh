while true; do
  make main-release -s && ./main-release &
	PID=$!
	inotifywait -e modify *.h *.cpp
	kill $PID
done

