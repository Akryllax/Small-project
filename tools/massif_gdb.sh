#!/bin/bash

# Start a new tmux session named "debug_session"
tmux new-session -d -s debug_session

# Split the window horizontally
tmux split-window -h

# Launch Valgrind in the first pane
tmux send-keys -t debug_session:0.0 'valgrind --tool=massif ./../build/dataGen' C-m

# Launch GDB in the second pane
tmux send-keys -t debug_session:0.1 'gdb -ex "target remote | vgdb"' C-m

# Attach to the tmux session to view the layout and commands
tmux attach-session -t debug_session

