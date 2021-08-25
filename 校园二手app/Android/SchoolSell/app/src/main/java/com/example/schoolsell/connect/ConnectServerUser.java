package com.example.schoolsell.connect;

import android.util.Log;

import com.example.schoolsell.beans.User;

import org.json.JSONObject;

import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import static android.system.Os.read;

public class ConnectServerUser {
    public static boolean userRegister(final User user,String end) {//传入对象和服务器路径
        new Thread() {
            @Override
            public void run() {
                try {
                    JSONObject userJSON = new JSONObject();
                    userJSON.put("Userid", user.getUserid());
                    userJSON.put("Userpassword", user.getUserpassword());
                    userJSON.put("Userphone", user.getUserphone());
                    String content = String.valueOf(userJSON);

                    //HttpURLConnection connection  =
                    /**
                     * 请求地址
                     */
                    String url = "http://www.localhost:8080" + end;

                    HttpURLConnection connection = (HttpURLConnection) new URL(url).openConnection();
                    //HttpURLConnection connection = (HttpURLConnection) nURL.openConnection();
                    connection.setConnectTimeout(5000);
                    connection.setRequestMethod("POST");
                    connection.setDoOutput(true);
                    connection.setRequestProperty("User-Agent", "Fiddler");
                    connection.setRequestProperty("Content-Type", "application/json");
                    connection.setRequestProperty("Charset", "UTF-8");
                    String result=connection.getResponseMessage();


                } catch (Exception e) {

                }
            }
        }.start();
        return true;
    }
}
