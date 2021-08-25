package com.example.schoolsell.adapter;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import java.util.ArrayList;

public class MyPagerAdapter extends FragmentPagerAdapter {
    private ArrayList<Fragment> framgments;
    private  String [] mTitles;
    public MyPagerAdapter(FragmentManager fm,String[] mTitles,ArrayList<Fragment> framgments){
        super(fm);
        this.mTitles=mTitles;
        this.framgments=framgments;
    }


    @Override
    public int getCount() {
        return framgments.size();
    }
    @Override
    public CharSequence getPageTitle(int position){return mTitles[position];}
    @Override
    public Fragment getItem(int position) {
        return framgments.get(position);
    }
}
