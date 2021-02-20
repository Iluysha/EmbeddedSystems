package com.example.lab32;

import androidx.appcompat.app.AppCompatActivity;
import android.annotation.SuppressLint;
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

    @SuppressLint({"SetTextI18n", "DefaultLocale"})
    public void Calculate(View view) {
        EditText editText = findViewById(R.id.p);
        int p = editText.getText().toString().equals("") ? 4 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.a_x);
        int a_x = editText.getText().toString().equals("") ? 0 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.a_y);
        int a_y = editText.getText().toString().equals("") ? 6 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.b_x);
        int b_x = editText.getText().toString().equals("") ? 1 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.b_y);
        int b_y = editText.getText().toString().equals("") ? 5 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.c_x);
        int c_x = editText.getText().toString().equals("") ? 3 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.c_y);
        int c_y = editText.getText().toString().equals("") ? 3 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.d_x);
        int d_x = editText.getText().toString().equals("") ? 2 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.d_y);
        int d_y = editText.getText().toString().equals("") ? 4 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.q);
        double q = editText.getText().toString().equals("") ? 0.01 :
                Double.parseDouble(editText.getText().toString());
        editText = findViewById(R.id.t);
        int t = editText.getText().toString().equals("") ? 1 :
                Integer.parseInt(editText.getText().toString());
        editText = findViewById(R.id.n);
        int n = editText.getText().toString().equals("") ? 100 :
                Integer.parseInt(editText.getText().toString());

        double w1 = 0, w2 = 0, delta;
        double start = System.nanoTime();

        for(int i = 0; i < n / 4; i++) {
            delta = p - (a_x * w1 + a_y * w2);
            w1 = w1 + delta * a_x * q;
            w2 = w2 + delta * a_y * q;
            if(System.nanoTime() - start > t * 1000000000){
                break;
            }

            delta = p - (b_x * w1 + b_y * w2);
            w1 = w1 + delta * b_x * q;
            w2 = w2 + delta * b_y * q;
            if(System.nanoTime() - start > t * 1000000000){
                break;
            }

            delta = p - (c_x * w1 + c_y * w2);
            w1 = w1 + delta * c_x * q;
            w2 = w2 + delta * c_y * q;
            if(System.nanoTime() - start > t * 1000000000){
                break;
            }

            delta = p - (d_x * w1 + d_y * w2);
            w1 = w1 + delta * d_x * q;
            w2 = w2 + delta * d_y * q;
            if(System.nanoTime() - start > t * 1000000000){
                break;
            }
        }

        TextView textView = findViewById(R.id.textView);
        textView.setText(String.format("W1 = %.3f, W2 = %.3f\nTime = %.3f ms, Delta = %.3f\n",
                w1, w2, (System.nanoTime() - start)/1000000, p - (a_x * w1 + a_y * w2)));
    }
}

