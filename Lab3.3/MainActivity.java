package com.example.lab33;

import androidx.appcompat.app.AppCompatActivity;
import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @SuppressLint("SetTextI18n")
    public void Calculate(View view) {
        TextView textView = findViewById(R.id.textView);
        EditText editText = findViewById(R.id.a);
        int a = editText.getText().toString().equals("") ? 2 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.b);
        int b = editText.getText().toString().equals("") ? 6 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.c);
        int c = editText.getText().toString().equals("") ? 1 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.d);
        int d = editText.getText().toString().equals("") ? 4 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.y);
        int y = editText.getText().toString().equals("") ? 17 :
                Integer.parseInt(editText.getText().toString());

        int max =  Math.max(Math.max(a, b), Math.max(c, d));
        if(a + b + c + d > y) {
            textView.setText("Incorrect input!");
            return;
        }

        Random random = new Random();
        int[][] gen = new int[][] {
                {random.nextInt(y / max + 1) + 1, random.nextInt(y / max + 1) + 1,
                        random.nextInt(y / max + 1) + 1, random.nextInt(y / max + 1) + 1},
                {random.nextInt(y / max + 1) + 1, random.nextInt(y / max + 1) + 1,
                        random.nextInt(y / max + 1) + 1, random.nextInt(y / max + 1) + 1},
                {random.nextInt(y / max + 1) + 1, random.nextInt(y / max + 1) + 1,
                        random.nextInt(y / max + 1) + 1, random.nextInt(y / max + 1) + 1},
                {random.nextInt(y / max + 1) + 1, random.nextInt(y / max + 1) + 1,
                        random.nextInt(y / max + 1) + 1, random.nextInt(y / max + 1) + 1}};

        int counter = 0;
        double start = System.nanoTime();
        
        while (true) {
            counter++;
            if(counter > 100000000) {
                textView.setText("Limit of iterations!");
                return;
            }
            int[] delta = new int[4];
            int sum_delta = 0;
            double[] fitness = new double[4];
            for (int i = 0; i < 4; i++) {
                delta[i] = Math.abs(a * gen[i][0] + b * gen[i][1] + c * gen[i][2] + d * gen[i][3] - y);
                if (delta[i] == 0) {
                    textView.setText(a + " * " + gen[i][0] + " + " +
                            b + " * " + gen[i][1] + " + " +
                            c + " * " + gen[i][2] + " + " +
                            d + " * " + gen[i][3] + " = " + y + "\n" +
                            "Number of iterations = " + counter + "\n" +
                            "Time = " + (System.nanoTime() - start)/1000000 + " ms\n");
                    return;
                }
                sum_delta += (double) 1 / delta[i];
            }

            for (int i = 0; i < 4; i++) {
                fitness[i] = (double) 1 / delta[i] / sum_delta;
            }

            //Sort gens by fitness function
            int[] keys = new int[]{0, 1, 2, 3};
            for (int i = 3; i > 0; i--) {
                for (int j = 0; j < i; j++) {
                    if (fitness[j] > fitness[j + 1]) {
                        double tmp = fitness[j];
                        fitness[j] = fitness[j + 1];
                        fitness[j + 1] = tmp;
                        int t = keys[j];
                        keys[j] = keys[j + 1];
                        keys[j + 1] = t;
                    }
                }
            }

            //Crossover of two parents with the best fitness function
            gen[keys[0]] = new int[]{gen[keys[2]][0], gen[keys[2]][1],
                    gen[keys[3]][2], gen[keys[3]][3]};
            gen[keys[1]] = new int[]{gen[keys[2]][2], gen[keys[2]][3],
                    gen[keys[3]][0], gen[keys[3]][1]};

            //Mutation
            gen[random.nextInt(3)][random.nextInt(3)]++;
            gen[random.nextInt(3)][random.nextInt(3)] =
                    gen[random.nextInt(3)][random.nextInt(3)];
        }
    }
}

