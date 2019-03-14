package tasks.task1;

public class Main {
    private void printTable(Integer table[][]) {
        for (int i = 0; i < table.length; ++i) {
            for (int j = 0; j < table[i].length; ++j) {
                System.out.print(table[i][j]);
                System.out.print(' ');
            }

            System.out.println();
        }
    }

    public static void main(String[] args) {
        Integer table[][] = { {1, 2}, {2, 3} };
        Main main = new Main();
        main.printTable(table);
    }
}
