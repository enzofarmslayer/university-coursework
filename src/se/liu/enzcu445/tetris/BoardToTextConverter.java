package se.liu.enzcu445.tetris;

public class BoardToTextConverter {
    public String convertToText(Board board) {
        StringBuilder builder = new StringBuilder();
        for (int y = 0; y < board.getHeight(); y++) {
            for (int x = 0; x < board.getWidth(); x++) {
                SquareType squareType = board.getVisibleSquaresAt(y,x);
                switch (squareType){
                    case EMPTY:
                        builder.append("-");
                        break;
                    case I:
                        builder.append("I");
                        break;
                    case O:
                        builder.append("O");
                        break;
                    case T:
                        builder.append("T");
                        break;
                    case S:
                        builder.append("S");
                        break;
                    case Z:
                        builder.append("Z");
                        break;
                    case J:
                        builder.append("J");
                        break;
                    case L:
                        builder.append("L");
                        break;
                    default:
                        builder.append("#");
                        break;
                }
            }
            builder.append("\n");
        }
        return builder.toString();
    }
}
