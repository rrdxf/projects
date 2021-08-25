package com.example.schoolsell.fragment;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.ListView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;
import androidx.viewpager.widget.PagerAdapter;
import androidx.viewpager.widget.ViewPager;

import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.adapter.IndexAdapter;
import com.example.schoolsell.beans.Good;
import com.example.schoolsell.connect.HttpUtil;
import com.example.schoolsell.connect.JSONUtil;
import com.example.schoolsell.pages.good_show;
import com.google.gson.reflect.TypeToken;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class IndexFragment extends Fragment {

    private IndexViewModel mViewModel;
    private View view=null;
    private ViewPager lubo=null;
    private List<Integer> mData=new ArrayList<>();

    private ListView index_list=null;
    private List<Map<String, Object>> list=null;

    public static IndexFragment newInstance() {
        return new IndexFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {

        view=inflater.inflate(R.layout.activity_index, container, false);
        index_list=view.findViewById(R.id.index_list);
        list=getData();
        index_list.setAdapter(new IndexAdapter(list,getActivity()));//index商品列表适配器
        return view;



    }
    public List<Map<String, Object>> getData(){
        MyApplication application = (MyApplication)this.getActivity().getApplication();
        List<Map<String, Object>> list=new ArrayList<Map<String,Object>>();

        List<Good> goods1=application.getGoods();
            if (goods1 != null) {
                for (Good good : goods1) {
                    Map<String, Object> map3 = new HashMap<String, Object>();
                    map3.put("goodid",good.getGoodid());
                    map3.put("goodname", good.getGoodname());
                    map3.put("goodprice", good.getGoodprice());
                    map3.put("goodexpression", good.getGoodexpression());
                    map3.put("goodimgelist", good.getGoodimgelist());
                    map3.put("ownericon", good.getOwner().getUsericon());
                    map3.put("ownername", good.getOwner().getUsername());
                    map3.put("ownerid", good.getOwner().getUserid());
                    list.add(map3);
                }

            } else {
                new Thread() {
                    @Override
                    public void run() {
                        HashMap<String, String> map = new HashMap<String, String>();
                        String result1 = HttpUtil.sendHttpRequest("/good/allgood", "POST", map);
                        Log.d("WTF", "result1:" + result1);
                        List<Good> goods = new ArrayList<>();
                        goods = JSONUtil.fromJsons(result1, new TypeToken<List<Good>>() {
                        }.getType());
                        application.setGoods(goods);
                        Log.d("WTW", "application.getGoods():" + application.getGoods());
                    }
                }.start();
            }

        Log.d("WTW","list:"+ list);
        return list;

    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(IndexViewModel.class);
        MyApplication application = (MyApplication)this.getActivity().getApplication();

        //轮播图的出现
        initView();
        initData();

        inilisenner(application);
    }

    private void inilisenner(MyApplication application) {
        index_list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                ///携带position和goodid跳转方便查询
                Log.d("III","parent:"+parent.toString());
                Intent intent=new Intent(IndexFragment.this.getActivity(), good_show.class);
                intent.putExtra("postion",position);
                intent.putExtra("goodid",(String) list.get(position).get("goodid"));
                intent.putExtra("goodname",(String) list.get(position).get("goodname"));
                intent.putExtra("goodprice",(String) list.get(position).get("goodprice"));
                intent.putExtra("goodexpression",(String) list.get(position).get("goodexpression"));
                intent.putExtra("usericon",(String)list.get(position).get("ownericon"));
                intent.putExtra("username",(String)list.get(position).get("ownername"));
                Log.d("OO","goodshow:");
                Log.d("OO","(String) list.get(position).get(goodid):"+(String) list.get(position).get("goodid"));


                startActivity(intent);
            }
        });
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
        lubo=view.findViewById(R.id.lubo);
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

}
