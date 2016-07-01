package com.exsample.toyomoly.ndksample;

import android.content.res.AssetManager;

public class SearchRouteCpp {

    static {
        System.loadLibrary("hello");
    }

    protected native String calcByCpp(AssetManager assetManager, double stLat, double stLng, double edLat, double edLng);

    AssetManager assetManager;

    public SearchRouteCpp(AssetManager assetManager) {
        this.assetManager = assetManager;
    }

    public String callCpp(double stLat, double stLng, double edLat, double edLng) {

        String result = calcByCpp(assetManager, stLat, stLng, edLat, edLng);
        return result;
    }
}
