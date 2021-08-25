package com.example.schoolsell.fragment;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.adapter.ShopcartAdapter;
import com.example.schoolsell.beans.Shopcart;
import com.example.schoolsell.connect.JSONUtil;
import com.google.gson.reflect.TypeToken;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static com.example.schoolsell.connect.HttpUtil.sendHttpRequest;


public class MessageFragment extends Fragment {

    private MessageViewModel mViewModel;
    private ListView list1=null;
    private TextView tv_shopcartotalprice=null;
    private Button btn_cartjiesuan=null;
    MyApplication application = null;

    public static MessageFragment newInstance() {
        return new MessageFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {

        View view=inflater.inflate(R.layout.activity_message, container, false);
        list1=view.findViewById(R.id.list);
        tv_shopcartotalprice=view.findViewById(R.id.tv_shopcartotalprice);
        btn_cartjiesuan=view.findViewById(R.id.btn_cartjiesuan);


        //initShopcart();
        List<Shopcart> list=getData();
        application=(MyApplication)this.getActivity().getApplication();

        Log.d("PPP","list:"+list);
        Log.d("PPP","application:"+application);
        //shopcart_list.setAdapter(new ShopcartAdapter(list,getActivity(),application));
        double sum=0;
        for (int i=0;i<application.getGoods().size();i++){
            for (int j=0;j<list.size();j++){
                if (list.get(j).getGood_id().equals(application.getGoods().get(i).getGoodid())){
                    sum=sum+Double.parseDouble(application.getGoods().get(i).getGoodprice());
                }
            }
        }
        tv_shopcartotalprice.setText(String.valueOf(sum));
        ShopcartAdapter adapter=new ShopcartAdapter(list,this.getActivity(),application,sum);
        list1.setAdapter(adapter);
        return view;
    }


    //初始化购物车数据
    private void initShopcart() {

        new Thread(){
            @Override
            public void run() {
                Map<String, String> map=new HashMap<>();
                map.put("userid",application.getUser().getUserid());
                String result=sendHttpRequest("/shopcart/loadshopcart","POST",map);
                Log.d("PPP","result:"+result);
                List<Shopcart>shopcarts=JSONUtil.fromJsons(result,new TypeToken<List<Shopcart>>(){}.getType());
                application.setShopcarts(shopcarts);
                Log.d("PPP","application.setShopcarts:"+application.getShopcarts());
            }
        }.start();

    }

    private List<Shopcart> getData() {
        application=(MyApplication)this.getActivity().getApplication();
        return application.getShopcarts();
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(MessageViewModel.class);
        // TODO: Use the ViewModel
    }

}
