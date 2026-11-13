package se.liu.enzcu445.tetris;

public class TetrominoMaker {

    public Poly getPoly(int n) {

        // Check if the provided index is within the valid range of Tetromino types.
        if (n < 0 || n >= SquareType.values().length) {
            throw new IllegalArgumentException("Invalid index: " + n);
        }

        // Create a Tetromino based on the provided index.
        switch (n) {
            case 0:
                return createBlockI();
            case 1:
                return createBlockJ();
            case 2:
                return createBlockL();
            case 3:
                return createBlockO();
            case 4:
                return createBlockS();
            case 5:
                return createBlockT();
            case 6:
                return createBlockZ();
            default:
                throw new IllegalArgumentException("Unknown block type");
        }
    }

    // Each method below returns a Poly object representing the Tetromino's shape.
    private Poly createBlockI() {
        SquareType[][] shape = {{SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY},
                {SquareType.I, SquareType.I, SquareType.I, SquareType.I},
                {SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY},
                {SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY}};
        return new Poly(shape);
    }

    private Poly createBlockJ() {
        SquareType[][] shape = {{SquareType.J, SquareType.EMPTY, SquareType.EMPTY},
                         {SquareType.J, SquareType.J, SquareType.J},
                         {SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY}};
        return new Poly(shape);
    }

    private Poly createBlockL() {
        SquareType[][] shape = {{SquareType.EMPTY, SquareType.EMPTY, SquareType.L},
                {SquareType.L, SquareType.L, SquareType.L},
                {SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY}};
        return new Poly(shape);
    }
    private Poly createBlockO() {
        SquareType[][] shape = {{SquareType.O, SquareType.O},
                         {SquareType.O, SquareType.O}};
        return new Poly(shape);
    }
    private Poly createBlockS() {
        SquareType[][] shape = {{SquareType.EMPTY, SquareType.S, SquareType.S},
                {SquareType.S, SquareType.S, SquareType.EMPTY},
                {SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY}};
        return new Poly(shape);
    }
    private Poly createBlockT() {
        SquareType[][] shape = {{SquareType.EMPTY, SquareType.T, SquareType.EMPTY},
                {SquareType.T, SquareType.T, SquareType.T},
                {SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY}};
        return new Poly(shape);
    }
    private Poly createBlockZ() {
        SquareType[][] shape = {{SquareType.Z, SquareType.Z, SquareType.EMPTY},
                {SquareType.EMPTY, SquareType.Z, SquareType.Z},
                {SquareType.EMPTY, SquareType.EMPTY, SquareType.EMPTY}};
        return new Poly(shape);
    }
}
