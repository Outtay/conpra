import java.awt.*;
import java.io.*;
import java.util.*;
import java.util.List;

import static java.lang.Math.atan2;
import static java.lang.Math.max;

public class Main {

    private static int testcases;
    private static int currentTestcase = 1;
    private static BufferedReader in;
    private static String currentLine;

    private static int n, w;
    private static int[] packagesAvailable, weightPerPackage, caloriesPerPackage;

    public static void main(String[] args) throws FileNotFoundException {


        in = new BufferedReader(new InputStreamReader(getInputStream()));

        try {
            currentLine = in.readLine();
            testcases = Integer.parseInt(currentLine);
            while (currentTestcase <= testcases) {
                doStuff();
                currentTestcase++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void doStuff() throws IOException {
        String[] input = in.readLine().split(" ");
        w = Integer.parseInt(input[0]);
        n = Integer.parseInt(input[1]);

        packagesAvailable = new int[n + 1];
        weightPerPackage = new int[n + 1];
        caloriesPerPackage = new int[n + 1];

        int[][] maxCalories = new int[n + 1][w + 1];
        int[][] itemsTaken = new int[n + 1][w + 1];

        Arrays.fill(maxCalories[0], 0);
        Arrays.fill(itemsTaken[0], 0);

        for(int i = 0; i <= n; i++){
            maxCalories[i][0] = 0;
            itemsTaken[i][0] = 0;
        }

        for (int currentArticle = 1; currentArticle <= n; currentArticle++) {
            input = in.readLine().split(" ");

            int available = Integer.parseInt(input[0]);
            int articleWeight = Integer.parseInt(input[1]);
            int calories = Integer.parseInt(input[2]);

            weightPerPackage[currentArticle] = articleWeight;

            for(int currentWeight = 1; currentWeight <= w; currentWeight++){
                maxCalories[currentArticle][currentWeight] = 0;
                for(int k = 0; k <= available; k++){
                    if(k * articleWeight > currentWeight){
                        break;
                    }

                    if(maxCalories[currentArticle][currentWeight] < k * calories + maxCalories[currentArticle - 1][currentWeight - k * articleWeight]){
                        maxCalories[currentArticle][currentWeight] = k * calories + maxCalories[currentArticle - 1][currentWeight - k * articleWeight];
                        itemsTaken[currentArticle][currentWeight] = k;
                    }
                }

            }
        }

        System.out.printf("Case #%d: %s\n", currentTestcase, resultString(itemsTaken));
        in.readLine();
    }

    private static String resultString(int[][] itemsTaken){
        StringBuilder sb = new StringBuilder();
        int weightLeft = w;
        int currentItem = n;
        while(weightLeft > 0 && currentItem > 0){
            for(int i = 1; i <= itemsTaken[currentItem][weightLeft]; i++){
                sb.append(currentItem).append(" ");
            }
            weightLeft = weightLeft - itemsTaken[currentItem][weightLeft] * weightPerPackage[currentItem];
            currentItem--;
        }

        return sb.reverse().toString().trim();
    }

    private static InputStream getInputStream() throws FileNotFoundException {
        //return new FileInputStream("src/week11/ex5/input.txt");
        return System.in;
    }

}