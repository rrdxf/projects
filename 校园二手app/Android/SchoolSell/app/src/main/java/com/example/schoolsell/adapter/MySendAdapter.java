package com.example.schoolsell.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.beans.Image;
import com.example.schoolsell.connect.container;
import com.example.schoolsell.fragment.MysendFragment;

import java.util.List;
import java.util.Map;

public class MySendAdapter extends BaseAdapter {
    private List<Map<String, Object>> data;
    private LayoutInflater layoutInflater;
    private Context context;
    private MyApplication application;
    public MySendAdapter(List<Map<String, Object>> data, Context context, MyApplication application ) {
        this.data = data;
        this.layoutInflater = LayoutInflater.from(context);
        this.context = context;
        this.application=application;
    }

    static class zujian{
        public ImageView mysend_iv_goodicon;
        public TextView mysend_tv_goodname;

       public TextView mysend_good_price;
       public Button mysend_btn_decentgood;

       public Button mysend_btn_decentgoodprice;

        public Button mysend_btn_edictgood;

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
        zujian zujian=null;
        if (convertView==null){
            zujian=new zujian();
            convertView=layoutInflater.inflate(R.layout.mysend_listview_item,null);
            zujian.mysend_btn_decentgood=(Button)convertView.findViewById(R.id.mysend_btn_decentgood);
            zujian.mysend_btn_decentgoodprice=(Button)convertView.findViewById(R.id.mysend_btn_decentgoodprice);
            zujian.mysend_btn_edictgood=(Button)convertView.findViewById(R.id.mysend_btn_edictgood);
            zujian.mysend_good_price=(TextView)convertView.findViewById(R.id.mysend_good_price);
            zujian.mysend_iv_goodicon=(ImageView) convertView.findViewById(R.id.mysend_iv_goodicon);
            zujian.mysend_tv_goodname=(TextView)convertView.findViewById(R.id.mysend_tv_goodname);
            convertView.setTag(zujian);
        }else {
            zujian=(zujian)convertView.getTag();
        }

        //绑定数据
        zujian.mysend_tv_goodname.setText(data.get(position).get("goodname").toString());

        zujian.mysend_good_price.setText("￥"+(String)data.get(position).get("goodprice"));
        List<Image>images=(List<Image>) data.get(position).get("goodimgelist");
        Glide.with(context).load(container.DOWNLOAD_URL+images.get(0).getImgsrc()).into(zujian.mysend_iv_goodicon);
        int currentPosition = position;//记录当前的位置
        MysendFragment mysendFragment;
        zujian.mysend_btn_decentgood.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //删除服务器数据
                //delete(goods_address_id);//根据接口删除服务器数据
                for (int i = 0; i <application.getGoods().size(); i++) {

                    if (application.getGoods().get(i).equals((String)data.get(position).get("goodid"))) {
                        application.getGoods().remove(i);
                    }
                }
                data.remove(currentPosition);//将集合中的数据删除

                notifyDataSetChanged();//更新适配器

            }
        });

        return convertView;
    }
}
