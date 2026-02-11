project('EZ Chess++', 'cpp', default_options : ['cpp_std=c++11'])

EZChess_src = [
    'AbstractPiece.cpp',
    'AbstractZone.cpp',
    'Bishop.cpp',
    'BlackAndWhitePiece.cpp',
    'ChessBoard.cpp',
    'ChessBoardWindow.cpp',
    'ez-draw++.cpp',
    'King.cpp',
    'Knight.cpp',
    'main.cpp',
    'Pawn.cpp',
    'Point.cpp',
    'Queen.cpp',
    'Rook.cpp',
    'SquareZone.cpp',
]

executable(
    'EZChess', EZChess_src ,
    dependencies : [ dependency('x11') , dependency('xext') ]
)
