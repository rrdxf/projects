package com.example.schoolsell;

import android.content.Intent;
import android.os.Bundle;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.schoolsell.beans.Good;
import com.example.schoolsell.beans.Shopcart;
import com.example.schoolsell.beans.User;
import com.example.schoolsell.connect.HttpUtil;
import com.example.schoolsell.connect.JSONUtil;
import com.example.schoolsell.connect.container;
import com.example.schoolsell.pages.Regsiter;
import com.google.gson.reflect.TypeToken;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static com.example.schoolsell.connect.HttpUtil.sendHttpRequest;


public class MainActivity extends AppCompatActivity {

    private ImageButton logon_btn_logon=null;
    private ImageButton logon_btn_register=null;

    private HashMap<String,String>map=null;
    private EditText et_infoid=null;
    private EditText et_password=null;
    private User main_user=new User();



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        logon_btn_logon=findViewById(R.id.logon_btn_logon);
        logon_btn_register=findViewById(R.id.logon_btn_register);

        et_infoid=findViewById(R.id.et_infoid);
        et_password=findViewById(R.id.et_password);




        logon_btn_logon.setOnClickListener(v -> new Thread(() -> {

            //获取登录个人的所有信息
            map=new HashMap<String, String>();
            map.put("Userid",et_infoid.getText().toString());
            map.put("Userpassword",et_password.getText().toString());
            String result= HttpUtil.sendHttpRequest("/user/login","POST",map);
            main_user= JSONUtil.fromJson(result,User.class);
            MyApplication application = (MyApplication) this.getApplication();

            new Thread(){
                @Override
                public void run() {
                    HashMap<String,String>map=new HashMap<String, String>();
                    String result1= HttpUtil.sendHttpRequest("/good/allgood","POST",map);
                    Log.d("WTF","result1:"+result1);
                    List<Good> goods=new ArrayList<>();
                    goods= JSONUtil.fromJsons(result1,new TypeToken<List<Good>>(){}.getType());
                    application.setGoods(goods);
                    Log.d("WTW","application.getGoods()getGoods().size():"+application.getGoods().size());
                }
            }.start();

            //获取所有的已发布物品信息，方便显示到主页

            if (main_user.getUserid()!=null) {

                main_user = JSONUtil.fromJson(result, User.class);
                application.setUser(main_user);
                application.setIslog(true);
                Log.d("WTF", "result:" + result);
                Intent intent = new Intent(MainActivity.this, IndexActivity.class);
                startActivity(intent);
                initShopcart(application);
                Looper.prepare();
                Toast.makeText(MainActivity.this, "登录成功", Toast.LENGTH_SHORT).show();
                Looper.loop();

            }
            else {
                Looper.prepare();
                Toast.makeText(MainActivity.this, "用户名或密码错误", Toast.LENGTH_SHORT).show();
                Looper.loop();

            }
        }).start());


        //登录页面向注册页面监听器
        logon_btn_register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(MainActivity.this, Regsiter.class);
                startActivity(intent);
                /*Log.d("ATF", "点击的相册");
                Intent intent=new Intent(Intent.ACTION_PICK);
                intent.setType("image/*");
                startActivityForResult(intent, 0);*/
            }
        });


    }
    private void initShopcart(MyApplication application) {

        new Thread(){
            @Override
            public void run() {
                Map<String, String> map=new HashMap<>();
                map.put("userid",application.getUser().getUserid());
                Log.d("PPP","container.BASE_URL+/shopcart/loadshopcart:"+container.BASE_URL+"/shopcart/loadshopcart");
                String result=sendHttpRequest("/shopcart/loadshopcart","POST",map);

                List<Shopcart>shopcarts=JSONUtil.fromJsons(result,new TypeToken<List<Shopcart>>(){}.getType());
                application.setShopcarts(shopcarts);
                Log.d("PPP","application.setShopcarts:"+application.getShopcarts());
            }
        }.start();

    }
   /* private void savegood(JSONObject jsonObject) {
        JSONArray ja= null;
        try {
            ja = jsonObject.getJSONArray("holdGood");
            List<Entity> holdGoodlist=;
                    main_user.setHoldGood(jsonObject.getString("holdGood"));
        } catch (JSONException e) {
            e.printStackTrace();
        }

    }*/
}

