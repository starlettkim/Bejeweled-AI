player: player.cc board.cc derived_board.cc
	g++ -std=c++11 -o player player.cc board.cc derived_board.cc
clean:
	rm player