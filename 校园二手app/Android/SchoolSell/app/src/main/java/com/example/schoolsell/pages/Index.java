package com.example.schoolsell.pages;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.PagerAdapter;
import androidx.viewpager.widget.ViewPager;

import com.example.schoolsell.R;

import java.util.ArrayList;
import java.util.List;

public class Index extends AppCompatActivity {
    private ViewPager lubo=null;
    private List<Integer> mData=new ArrayList<>();




    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_index);

    }
   //轮播图
    private void initData() {
        mData.add(R.mipmap.lunbo5);
        mData.add(R.mipmap.lunbo6);
        mData.add(R.mipmap.lunbo7);
        mData.add(R.mipmap.lunbo4);
        mPagerAdapter.notifyDataSetChanged();
    }

    private void initView(){
        lubo=this.findViewById(R.id.lubo);
        lubo.setAdapter(mPagerAdapter);
    }
    private PagerAdapter mPagerAdapter=new PagerAdapter() {
        private static final String ATG = "";

        @Override
        public int getCount() {
            // Log.d(ATG,"");
            return Integer.MAX_VALUE;
        }

        @Override
        public boolean isViewFromObject(@NonNull View view, @NonNull Object object) {
            return view==object;
        }

        @NonNull
        @Override
        public Object instantiateItem(@NonNull ViewGroup container, int position) {
            View item= LayoutInflater.from(container.getContext()).inflate(R.layout.item_pager,container,false);
            ImageView iv=item.findViewById(R.id.cover);

            //设置数据
            if(iv.getParent()instanceof ViewGroup){
                ((ViewGroup)iv.getParent()).removeView(iv);
            }
            int realPosition=position%mData.size();

            iv.setImageResource(mData.get(realPosition));
            container.addView(iv);
            return iv;
        }

        @Override
        public void destroyItem(@NonNull ViewGroup container, int position, @NonNull Object object) {
            container.removeView((View) object);
        }
    };
   /* ///底部导航栏
    private BottomNavigationView.OnNavigationItemSelectedListener mOnNavigationItemSelectedListener
            = new BottomNavigationView.OnNavigationItemSelectedListener() {

        @Override
        public boolean onNavigationItemSelected(@NonNull MenuItem item) {
            switch (item.getItemId()) {
                case R.id.index:

                    return true;
                case R.id.message:

                    return true;
                case R.id.sendgood:

                    return true;
                case R.id.mysend:

                    return true;
                case R.id.mine:

                    return true;
            }
            return false;
        }
    };

    AppBarConfiguration appBarConfiguration = new AppBarConfiguration.Builder(
            R.id.index, R.id.message, R.id.sendgood, R.id.mysend,R.id.mine)
            .build();

*/



}
