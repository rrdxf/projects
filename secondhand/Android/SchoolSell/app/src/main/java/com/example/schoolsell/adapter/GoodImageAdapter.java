package com.example.schoolsell.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;

import com.bumptech.glide.Glide;
import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.beans.Image;
import com.example.schoolsell.connect.container;

import java.util.List;

public class GoodImageAdapter extends BaseAdapter {
    private List<Image> data;
    private LayoutInflater layoutInflater;
    private Context context;
    private MyApplication application;
    private String goodid;

    public GoodImageAdapter(List<Image> data, Context context, MyApplication application ) {
        this.data = data;
        this.layoutInflater = LayoutInflater.from(context);
        this.context = context;
        this.application=application;
        this.goodid=goodid;
    }
    static class zujian{
        public ImageView goodimage_item;
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
        convertView=layoutInflater.inflate(R.layout.good_imagelist_item,null);
        zujian zujian=new zujian();
        zujian.goodimage_item=convertView.findViewById(R.id.goodimage_item);

        Glide.with(context).load(container.DOWNLOAD_URL+data.get(position).getImgsrc()).into(zujian.goodimage_item);
        return convertView;
    }

}
