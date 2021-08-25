package com.example.schoolsell.adapter;

import android.content.Context;
import android.os.Looper;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;
import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.beans.Good;
import com.example.schoolsell.beans.Shopcart;
import com.example.schoolsell.connect.container;

import java.util.HashMap;
import java.util.List;

import static com.example.schoolsell.connect.HttpUtil.sendHttpRequest;

public class ShopcartAdapter extends BaseAdapter {
    private List<Shopcart> data;
    private LayoutInflater layoutInflater;
    private Context context;
    private MyApplication application;
    private double sum;
    public ShopcartAdapter(List<Shopcart> data, Context context ,MyApplication application,double sum) {
        this.data = data;
        this.layoutInflater = LayoutInflater.from(context);
        this.context = context;
        this.application=application;
    }
    static class zujian{
       public ImageView shopcart_iv_goodicon;
       public TextView shopcart_tv_goodname;
       public TextView shopcart_good_price;
       public Button shopcart_btn_deletgood;
    }
    @Override
    public int getCount() {
        return data.size();
    }

    @Override
    public Object getItem(int position) {
        return data.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        zujian zujian=new zujian();
        convertView=layoutInflater.inflate(R.layout.message_listview_item,null);
        zujian.shopcart_iv_goodicon=convertView.findViewById(R.id.shopcart_iv_goodicon);
        zujian.shopcart_btn_deletgood=convertView.findViewById(R.id.shopcart_btn_deletgood);
        zujian.shopcart_tv_goodname=convertView.findViewById(R.id.shopcart_tv_goodname);
        zujian.shopcart_good_price=convertView.findViewById(R.id.shopcart_good_price);
        convertView.setTag(zujian);

        //Log.d("SSSWWW","application.getGoods()："+application.getGoods().size());
         Good good=new Good();
        Log.d("SSSWWW","*************************************");
        for(int i=0;i<application.getGoods().size();i++){

            if (application.getGoods().get(i).getGoodid().equals(data.get(position).getGood_id())){

                good=application.getGoods().get(i);
                break;
            }
        }
        Log.d("SSSWWW","*************************************"+good.toString());
        zujian.shopcart_good_price.setText(good.getGoodprice());
        zujian.shopcart_tv_goodname.setText(good.getGoodname());
        Log.d("SSSWWW","container.DOWNLOAD_URL+good.getGoodimgelist().get(0):"+container.DOWNLOAD_URL+good.getGoodimgelist().get(0));
        Glide.with(context).load(container.DOWNLOAD_URL+good.getGoodimgelist().get(0).getImgsrc()).into(zujian.shopcart_iv_goodicon);
        int currentPosition = position;//记录当前的位置

        final String price=good.getGoodprice();
        final String goodid=good.getGoodid();
        zujian.shopcart_btn_deletgood.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                for (int i = 0; i <application.getGoods().size(); i++) {

                    if (application.getShopcarts().get(i).getGood_id().equals(data.get(position).getGood_id())) {
                        application.getShopcarts().remove(i);
                        break;
                    }
                }
                //data.remove(currentPosition);//将集合中的数据删除
                new Thread(){
                    @Override
                    public void run() {
                        HashMap<String ,String>map=new HashMap<>();
                        map.put("userid",application.getUser().getUserid());
                        map.put("goodid",goodid);
                        String result=sendHttpRequest("/shopcart/deletgoodtocart","POST",map);
                        if (result!=null){
                            Looper.prepare();
                            Toast.makeText(context, "移出成功！", Toast.LENGTH_SHORT).show();
                            Looper.loop();
                        }
                    }
                }.start();
                sum=sum-Double.parseDouble(price);
//                application.getShopcarts().get(currentPosition).setTotalprice(String.valueOf(sum));
                notifyDataSetChanged();//更新适配器
            }
        });
        return convertView;
    }
}
