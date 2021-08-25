package com.example.schoolsell;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.viewpager.widget.ViewPager;

import com.example.schoolsell.adapter.MyPagerAdapter;
import com.example.schoolsell.entity.TabEntity;
import com.example.schoolsell.fragment.AddFragment;
import com.example.schoolsell.fragment.IndexFragment;
import com.example.schoolsell.fragment.MessageFragment;
import com.example.schoolsell.fragment.MineFragment;
import com.example.schoolsell.fragment.MysendFragment;
import com.flyco.tablayout.CommonTabLayout;
import com.flyco.tablayout.listener.CustomTabEntity;
import com.flyco.tablayout.listener.OnTabSelectListener;

import java.util.ArrayList;

public class IndexActivity extends AppCompatActivity {
    ///底部导航栏
    private ArrayList<Fragment> framgments =new ArrayList<>();
    private ArrayList<CustomTabEntity>tabEntities=new ArrayList<>();
    private  String [] mTitles={"首页","消息"," ","我的货物","我的"};
    private  int[] mIconUnselectIds={R.mipmap.index1,R.mipmap.car1,
            R.mipmap.add,R.mipmap.chargo1,R.mipmap.mine1};
    private  int[] mIconselectIds={R.mipmap.index,R.mipmap.car,R.mipmap.add,R.mipmap.chargo,R.mipmap.mine};
    private CommonTabLayout commonTabLayout;
    private ViewPager index_viewpager;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_index2);

        commonTabLayout=findViewById(R.id.navigation_index);
        index_viewpager=findViewById(R.id.index_viewpager);

        //底部导航栏
        framgments.add(IndexFragment.newInstance());
        framgments.add(MessageFragment.newInstance());
        framgments.add(AddFragment.newInstance());
        framgments.add(MysendFragment.newInstance());
        framgments.add(MineFragment.newInstance());


        for (int i =0;i<mTitles.length;i++){
            tabEntities.add(new TabEntity(mTitles[i],mIconselectIds[i],mIconUnselectIds[i]));
        }
        commonTabLayout.setTabData(tabEntities);
        commonTabLayout.setOnTabSelectListener(new OnTabSelectListener() {
            @Override
            public void onTabSelect(int position) {
                index_viewpager.setCurrentItem(position);
            }

            @Override
            public void onTabReselect(int position) {

            }
        });
        index_viewpager.setAdapter(new MyPagerAdapter(getSupportFragmentManager(),mTitles,framgments));
    }
}
