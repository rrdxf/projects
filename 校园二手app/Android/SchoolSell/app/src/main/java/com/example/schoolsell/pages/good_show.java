package com.example.schoolsell.pages;

import android.content.Intent;
import android.os.Bundle;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.bumptech.glide.Glide;
import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.adapter.GoodImageAdapter;
import com.example.schoolsell.beans.Image;
import com.example.schoolsell.beans.Shopcart;
import com.example.schoolsell.connect.container;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import static com.example.schoolsell.connect.HttpUtil.sendHttpRequest;

public class good_show extends AppCompatActivity {


    private ImageView iv_head_portrait=null;
    private TextView tv_username=null;
    //private TextView tv_location=null;
    private TextView tv_price=null;
    private TextView tv_goodname=null;
    private TextView tv_expression=null;
    private ListView good_image_list=null;
    private Button btn_cart=null;
    private String goodid=null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_good_show);

        btn_cart=findViewById(R.id.btn_cart);
        iv_head_portrait=findViewById(R.id.iv_head_portrait);
        tv_username=findViewById(R.id.tv_username);
        tv_price=findViewById(R.id.tv_price);
        tv_goodname=findViewById(R.id.tv_goodname);
        tv_expression=findViewById(R.id.tv_expression);
        good_image_list=findViewById(R.id.good_image_list);
        MyApplication application = (MyApplication) this.getApplication();
        Intent intent=getIntent();
        String position=intent.getStringExtra("postion");
        String goodname = intent.getStringExtra("goodname");
        goodid = intent.getStringExtra("goodid");
        Log.d("WTFAAAAAA", "goodid:"+goodid);
        Log.d("WTFAAAAAA", "intent.getStringExtra(goodid):"+intent.getStringExtra("goodid"));
        String goodexpression = intent.getStringExtra("goodexpression");
        String goodprice = intent.getStringExtra("goodprice");
        String ownericon=intent.getStringExtra("usericon");
        String ownername=intent.getStringExtra("username");
        application.setGood_show_goodid(goodid);

        Glide.with(this).load(container.DOWNLOAD_URL+ownericon).into(iv_head_portrait);
        tv_username.setText(ownername);
        tv_goodname.setText(goodname);
        tv_price.setText(goodprice);
        tv_expression.setText(goodexpression);

        //获取物品id对应的图片list

        List<Image> imageList=new ArrayList<Image>();
        for (int i=0;i<application.getGoods().size();i++){
            if (application.getGoods().get(i).getGoodid().equals(goodid)){
                imageList=application.getGoods().get(i).getGoodimgelist();
                break;
            }
        }


        good_image_list.setAdapter(new GoodImageAdapter(imageList,this,application));



        btn_cart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                HashMap<String,String>map=new HashMap<>();
                String Goodid=goodid;

                new Thread(){
                    @Override
                    public void run() {
                        Intent intent1=getIntent();
                        String goodid1 = intent1.getStringExtra("goodid");
                        map.put("userid",application.getUser().getUserid());
                        map.put("goodid",Goodid);
                        Log.d("WTFAAAAAA", "Goodid:"+Goodid);
                        Log.d("WTFAAAAAA","map:"+map);
                       String result=sendHttpRequest("/shopcart/addgoodtocart","POST",map);//数据库记录数据
                       if (result!=null){
                           Looper.prepare();
                           Toast.makeText(good_show.this, "成功添加入购物车", Toast.LENGTH_SHORT).show();
                           Looper.loop();
                           application.getShopcarts().add(new Shopcart(application.getUser().getUserid(),goodid));//将数据添加至购物车
                       }
                    }
                }.start();


            }
        });
    }
}
