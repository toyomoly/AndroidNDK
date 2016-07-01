package com.exsample.toyomoly.ndksample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.exsample.toyomoly.ndksample.SearchRouteCpp;

public class MainActivity extends AppCompatActivity {

    private double currentLat = 35.7119861;
    private double currentLng = 139.7766732;

    private double targetLat = 35.7121109;
    private double targetLng = 139.7765332;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btnCpp).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick (View v){
                TextView txtCpp = (TextView) findViewById(R.id.txtCpp);

                long start = System.currentTimeMillis();

                SearchRouteCpp search = new SearchRouteCpp(getResources().getAssets());
                String result = search.callCpp(currentLat, currentLng, targetLat, targetLng);

                long end = System.currentTimeMillis();

                txtCpp.setText("time: " + (end - start) + " ms [ len = " + result.length() + " ]");
            }
        });
    }
}
