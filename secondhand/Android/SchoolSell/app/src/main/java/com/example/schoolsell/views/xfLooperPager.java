package com.example.schoolsell.views;

import android.content.Context;
import android.os.Build;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.LinearLayout;

import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;

import com.example.schoolsell.R;

public class xfLooperPager extends LinearLayout {
    public xfLooperPager(Context context) {
        this(context,null);

    }

    public xfLooperPager(Context context, @Nullable AttributeSet attrs) {
        this(context, attrs,0);

    }

    public xfLooperPager(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        LayoutInflater.from(context).inflate(R.layout.looper_pager_layout,this,true);
    }


}
