package com.example.lab31;

import android.annotation.SuppressLint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @SuppressLint("SetTextI18n")
    public void Calculate(View view) {
        EditText editText = findViewById(R.id.edit_message);
        TextView textView = findViewById(R.id.textView);
        if(editText.getText().toString().equals("")) {
            textView.setText("Input number!");
            return;
        }
        int num = Integer.parseInt(editText.getText().toString());
        if(num == 0) {
            textView.setText("Incorrect number!");
            return;
        }

        double start = System.nanoTime();

        if(num % 2 == 0) {
            textView.setText(num + " = " + 2 + " * " + num / 2);
        } else {
            int x = (int) Math.sqrt(num);
            if (num == x * x) {
                textView.setText(num + " = " + x + " * " + x);
            } else {
                while (true) {
                    x++;
                    if((System.nanoTime() - start)/1000000000 > 1){
                        textView.setText("Time exhausted!");
                        break;
                    }
                    double y = Math.sqrt(Math.pow(x, 2) - num);
                    if (y % 1 == 0) {
                        textView.setText(num + " = " + (x - (int) y) + " * " + (x + (int) y) +
                                "\n" + "Time = " + (System.nanoTime() - start)/1000000 + " ms\n");
                        break;
                    }
                }
            }
        }
    }
}
