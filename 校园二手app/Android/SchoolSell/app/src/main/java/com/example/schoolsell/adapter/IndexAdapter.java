package com.example.schoolsell.adapter;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.example.schoolsell.R;
import com.example.schoolsell.beans.Image;
import com.example.schoolsell.connect.container;
import com.makeramen.roundedimageview.RoundedImageView;

import java.util.List;
import java.util.Map;

public class IndexAdapter extends BaseAdapter {

    private List<Map<String, Object>> data;
    private LayoutInflater layoutInflater;
    private Context context;

    public IndexAdapter(List<Map<String, Object>> data, Context context) {
        this.data = data;
        this.layoutInflater = LayoutInflater.from(context);
        this.context = context;
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

    static class indexzujian{
        ImageView index_chargo_icon;
        TextView index_info_name;
        TextView index_chargo_name;
        TextView index_chargo_express;
        TextView index_chargo_price;
        RoundedImageView index_info_icon;

    }
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        indexzujian indexzujian=null;
        if (convertView==null){
            indexzujian=new indexzujian();
            convertView=layoutInflater.inflate(R.layout.listview_item,null);
            indexzujian.index_chargo_icon=convertView.findViewById(R.id.index_chargo_icon);
            indexzujian.index_info_name=convertView.findViewById(R.id.index_info_name);
            indexzujian.index_chargo_name=convertView.findViewById(R.id.index_chargo_name);
            indexzujian.index_chargo_express=convertView.findViewById(R.id.index_chargo_express);
            indexzujian.index_chargo_price=convertView.findViewById(R.id.index_chargo_price);
            indexzujian.index_info_icon=convertView.findViewById(R.id.index_info_icon);


            convertView.setTag(indexzujian);
        }else {
            indexzujian=(indexzujian)convertView.getTag();
        }

        //绑定数据

        //Log.d("WTF","data.get(position).get(goodname):"+data.get(position).get("goodname"));

        //zujian.mysend_iv_goodicon.setBackgroundResource();

        List<Image>images=(List<Image>) data.get(position).get("goodimgelist");
        String icon_src=(String) data.get(position).get("ownericon");

        Glide.with(context).load(container.DOWNLOAD_URL+images.get(0).getImgsrc()).into(indexzujian.index_chargo_icon);
        Glide.with(context).load(container.DOWNLOAD_URL+(String) data.get(position).get("ownericon")).into(indexzujian.index_info_icon);
        Log.d("WTF","container.DOWNLOAD_URL+(String) data.get(position).get(ownericon):"+container.DOWNLOAD_URL+(String) data.get(position).get("ownericon"));
        indexzujian.index_chargo_price.setText("￥"+(String)data.get(position).get("goodprice"));
        indexzujian.index_chargo_name.setText((String)data.get(position).get("goodname"));
        indexzujian.index_chargo_express.setText((String)data.get(position).get("goodexpression"));
        indexzujian.index_info_name.setText((String)data.get(position).get("ownername"));
        Log.d("WTF","index：container.BASE_URL+images.get(0).getImgsrc():"+container.BASE_URL+images.get(0).getImgsrc());
        Log.d("WTF","index：data.get(position).get(goodname):"+(String)data.get(position).get("goodname"));
        //Log.d("WTF","images.get(0).getImgsrc():"+images.get(0).getImgsrc());
        return convertView;
    }
}
