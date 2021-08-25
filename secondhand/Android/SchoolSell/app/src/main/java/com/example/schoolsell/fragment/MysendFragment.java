package com.example.schoolsell.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.adapter.MySendAdapter;
import com.example.schoolsell.beans.Good;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MysendFragment extends Fragment {

    private MysendViewModel mViewModel;
    private View view=null;
    private ListView listView=null;
    MyApplication application = null;
    public static MysendFragment newInstance() {
        return new MysendFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        view=inflater.inflate(R.layout.activity_my_send, container, false);
        listView = (ListView) view.findViewById(R.id.mysend_list);
        List<Map<String, Object>> list=getData();
        //Log.d("WTF","list.toString():"+list.toString());
        application=(MyApplication)this.getActivity().getApplication();
        listView.setAdapter(new MySendAdapter(list,getActivity(),application));
        return view;
    }


    public List<Map<String, Object>> getData(){
        List<Map<String, Object>> list=new ArrayList<Map<String,Object>>();
        application=(MyApplication)this.getActivity().getApplication();
        List<Good>goods=application.getUser().getHoldGood();
        for (Good good:goods) {

            Map<String, Object> map=new HashMap<String, Object>();
            map.put("goodname", good.getGoodname());
            map.put("goodprice", good.getGoodprice());
            map.put("goodimgelist",good.getGoodimgelist());
            map.put("goodid",good.getGoodid());
            list.add(map);
        }
        return list;
    }



    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(MysendViewModel.class);
        MyApplication application = (MyApplication)this.getActivity().getApplication();

        initlisenner();

        // TODO: Use the ViewModel
    }

    private void initlisenner() {
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            }
        });
    }



}
