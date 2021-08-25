package com.example.schoolsell.pages;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Application;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.beans.User;
import com.makeramen.roundedimageview.RoundedImageView;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;

import static com.example.schoolsell.connect.HttpUtil.sendHttpRequest;

public class Mine extends AppCompatActivity {

    private RoundedImageView mine_info_icon=null;
    private TextView mine_tv_infoname=null;
    private TextView mine_tv_infoid=null;
    private TextView mine_tv_shoucang=null;
    private TextView mine_tv_lishi=null;
    private TextView mine_tv_guanzhu=null;
    private TextView mine_tv_fensi=null;
    private String end="user/uploadicon";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mine);
        Log.d("WTF","======================================");

       init();

    }

    private void init() {
        //获取登录信息中的全局变量

        MyApplication application = (MyApplication)this.getApplication();
        User user=new User();
        user=application.getUser();//new一个user对象来存取全局user变量
        Log.d("WTF","user:"+user.toString());
        mine_tv_infoname.setText(user.getUsername());
        mine_tv_infoid.setText("账号："+user.getUserid());
        final String userid=user.getUserid();
        new Thread(){
            @Override
            public void run(){

                Map<String,String> mine_map = new HashMap<String,String>();//http请求的map
                InputStream in;
                mine_map.put("fileName","icon_"+userid);
                String result=sendHttpRequest(end,"POST",mine_map);

                Log.d("WTF","result:"+result.toString());
            }
        }.start();
    }
}
