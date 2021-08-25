package com.example.schoolsell.pages;

import android.content.Intent;
import android.os.Bundle;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.schoolsell.MainActivity;
import com.example.schoolsell.R;
import com.example.schoolsell.beans.User;

import java.util.HashMap;
import java.util.Map;

import static com.example.schoolsell.connect.HttpUtil.sendHttpRequest;

public class Regsiter extends AppCompatActivity {

    private TextView register_tv_logon=null;
    private ImageButton register_btn_register=null;

    private EditText et_regsiter_infoid=null;
    private EditText et_regsiter_password=null;
    private EditText et_regsiter_password1=null;
    private EditText et_regsiter_phone=null;

    private User user=null;
    private Map<String,String> map = new HashMap<String,String>();//传递json数据的map对象


    private String end="/user/register";//服务器路径
    private String result="";//接受json返回的结
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_regsiter);

        register_tv_logon=findViewById(R.id.register_tv_logon);
        register_btn_register=findViewById(R.id.register_btn_register);

        et_regsiter_infoid=findViewById(R.id.et_regsiter_infoid);
        et_regsiter_password=findViewById(R.id.et_regsiter_password);
        et_regsiter_password1=findViewById(R.id.et_regsiter_password1);
        et_regsiter_phone=findViewById(R.id.et_regsiter_phone);


        //注册按钮事件监听
       register_btn_register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if((et_regsiter_infoid.getText().toString().equals(""))||(et_regsiter_phone.getText().toString().equals(""))||(et_regsiter_password.getText().toString().equals(""))||(et_regsiter_password1.getText().toString().equals("")))
                {

                    Toast.makeText(Regsiter.this, "请填入完整注册信息", Toast.LENGTH_LONG).show();

                }else {
                    Log.d("WTF", "et_regsiter_infoid.getText().toString():"+et_regsiter_infoid.getText().toString());
                    user = new User();
                    user.setUserid(et_regsiter_infoid.getText().toString());
                    user.setUserphone(et_regsiter_phone.getText().toString());

                    if (et_regsiter_password.getText().toString().equals(et_regsiter_password1.getText().toString())) {//
                        user.setUserpassword(et_regsiter_password.getText().toString());
                    }else{
                        Looper.prepare();
                        Toast.makeText(Regsiter.this, "两次密码输入不一致请检查", Toast.LENGTH_LONG).show();
                        Looper.loop();
                    }

                    map.put("Userid",user.getUserid());
                    map.put("Userpassword",user.getUserpassword());
                    map.put("Userphone",user.getUserphone());


                    Log.d("WTF", "result:"+result);
                    new Thread(){
                        @Override
                        public void run() {
                            Log.d("WTF", "map:"+map);
                            result=sendHttpRequest(end,"POST",map);

                        }
                    }.start();



                    ///发送数据


                    //注册成功

                    Toast.makeText(Regsiter.this, "注册成功", Toast.LENGTH_LONG).show();

                    Intent intent=new Intent(Regsiter.this, MainActivity.class);
                    startActivity(intent);


                }

            }
        });



        //蓝色登录按钮跳转监听器
        register_tv_logon.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(Regsiter.this, MainActivity.class);
                startActivity(intent);
            }
        });
    }


}
