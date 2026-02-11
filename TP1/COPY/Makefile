CXX=g++
CXXFLAGS=-Wall -O0

LIBS=-lXext -lX11
EXEC=prog

$(EXEC) : AbstractPiece.o AbstractZone.o Bishop.o BlackAndWhitePiece.o ChessBoard.o ChessBoardWindow.o ez-draw++.o King.o Knight.o main.o Pawn.o Point.o Queen.o Rook.o SquareZone.o
	$(CXX) -o $@ $^ $(LIBS)

AbstractPiece.o: AbstractPiece.cpp ez-draw++.hpp AbstractPiece.hpp Point.hpp Chess.hpp
	$(CXX) $(CXXFLAGS) -c $<

AbstractZone.o: AbstractZone.cpp ez-draw++.hpp AbstractZone.hpp Point.hpp Chess.hpp AbstractPiece.hpp
	$(CXX) $(CXXFLAGS) -c $<
Bishop.o: Bishop.cpp ez-draw++.hpp AbstractZone.hpp Point.hpp Chess.hpp Bishop.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp
	$(CXX) $(CXXFLAGS) -c $<
BlackAndWhitePiece.o: BlackAndWhitePiece.cpp ez-draw++.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp Point.hpp Chess.hpp AbstractZone.hpp
	$(CXX) $(CXXFLAGS) -c $<
ChessBoard.o: ChessBoard.cpp ez-draw++.hpp ChessBoard.hpp SquareZone.hpp AbstractZone.hpp Point.hpp Chess.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp King.hpp Queen.hpp Bishop.hpp Knight.hpp Rook.hpp Pawn.hpp
	$(CXX) $(CXXFLAGS) -c $<
ChessBoardWindow.o: ChessBoardWindow.cpp ChessBoardWindow.hpp ez-draw++.hpp ChessBoard.hpp SquareZone.hpp AbstractZone.hpp Point.hpp Chess.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp
	$(CXX) $(CXXFLAGS) -c $<
ez-draw++.o: ez-draw++.cpp ez-draw++.hpp
	$(CXX) $(CXXFLAGS) -c $<
King.o: King.cpp ez-draw++.hpp AbstractZone.hpp Point.hpp Chess.hpp King.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp
	$(CXX) $(CXXFLAGS) -c $<
Knight.o: Knight.cpp ez-draw++.hpp ChessBoard.hpp SquareZone.hpp AbstractZone.hpp Point.hpp Chess.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp Knight.hpp
	$(CXX) $(CXXFLAGS) -c $<
main.o: main.cpp ChessBoardWindow.hpp ez-draw++.hpp ChessBoard.hpp SquareZone.hpp AbstractZone.hpp Point.hpp Chess.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp
	$(CXX) $(CXXFLAGS) -c $<
Pawn.o: Pawn.cpp ez-draw++.hpp AbstractZone.hpp Point.hpp Chess.hpp Pawn.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp
	$(CXX) $(CXXFLAGS) -c $<
Point.o: Point.cpp ez-draw++.hpp Point.hpp Chess.hpp
	$(CXX) $(CXXFLAGS) -c $<
Queen.o: Queen.cpp ez-draw++.hpp AbstractZone.hpp Point.hpp Chess.hpp Queen.hpp BlackAndWhitePiece.hpp AbstractPiece.hpp
	$(CXX) $(CXXFLAGS) -c $<
SquareZone.o: SquareZone.cpp ez-draw++.hpp SquareZone.hpp AbstractZone.hpp Point.hpp Chess.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f *.o
	rm -f $(EXEC)
