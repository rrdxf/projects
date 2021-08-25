package com.example.schoolsell.connect;

import android.util.Log;

import com.example.schoolsell.entity.LoadFileVo;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;
import java.util.Map;
import java.util.concurrent.FutureTask;

import okhttp3.FormBody;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import okhttp3.ResponseBody;

import static com.example.schoolsell.connect.FileUtil.externalFilesDir;

public class HttpUtil {

    public static OkHttpClient client;
   private static final String domainName = "http://192.168.137.1:8080";//域名

    //private static final String domainName = "http://10.128.121.244:8080";//域名

    static {//创建OkHttpClient实例
        client = new OkHttpClient();
    }

    //默认发送GET请求，若发送的为GET请求，则传递参数为"GET", null, null
    //若发送的为POST请求，则需要传递一个Map对象，将需要传递的数据放在其中
    public static String sendHttpRequest(String url, String method, Map<String, String> map){
        Request.Builder requestBuilder = new Request.Builder();//创建Request.Builder
        requestBuilder.url(domainName+url);//添加URL
        Log.d("WTF", "url:"+domainName+url);
        if(method.equals("POST")){//若请求类型为POST，则需要获取要发送的数据，并调用post方法
            Log.d("WTF", "map:"+map.toString());
            FormBody.Builder requestBodyBuilder = new FormBody.Builder();
            for(Map.Entry<String, String> entry: map.entrySet()){
                requestBodyBuilder.add(entry.getKey(),entry.getValue());
            }
            requestBuilder.post(requestBodyBuilder.build());
        }
        // 添加请求类型
        MultipartBody.Builder builder = new MultipartBody.Builder();
        builder.setType(MediaType.parse("multipart/form-data"));
        Request request = requestBuilder.build();//获取Request实例
        try {//获取服务器响应，将返回数据转换为字符串并返回
            Response response = client.newCall(request).execute();

            return response.body().string();
        } catch (IOException e) {
            e.printStackTrace();
            return  "123";//若获取服务器响应数据失败，则
        }
    }

   //下载文件 fileName格式:/user/admin.jpg
    public static void downloadFile(String fileName){
        if(fileName==null||fileName.isEmpty())
            return;
        RequestBody requestBody = new MultipartBody.Builder()
                .addFormDataPart("fileName", fileName)
                .build();
        FutureTask<File> task = new FutureTask<>(()->{
            ResponseBody responseBody = client.newCall(
                    new Request.Builder()
                            .post(requestBody)
                            .url(domainName+"/download")
                            .build())
                    .execute()
                    .body();
            if(responseBody!=null){

                if(!externalFilesDir.isEmpty()){
                    File file = new File(externalFilesDir+fileName);
                    try(
                            InputStream in = responseBody.byteStream();
                            FileOutputStream out = new FileOutputStream(file);
                    ){
                        byte[] buf = new byte[1024];
                        int n;
                        if((n=in.read(buf))!=-1){
                            out.write(buf, 0, n);
                            while ((n=in.read(buf))!=-1)
                                out.write(buf, 0, n);
                            return file;
                        }else{
                            file.delete();
                            return null;
                        }
                    }catch (Exception e){ e.printStackTrace(); }
                }
            }
            return null;
        });
        task.run();
    }

    //向服务器上传文件
    public static String uploadFile(Map<String, String> map, LoadFileVo loadpickfile){
        String userid = map.get("userid");

       // new Thread(() -> {
            try {
                String url = "http://192.168.137.1:8080/user/uploadicon";
                String path =loadpickfile.getFile().getPath();
                String filename=loadpickfile.getFile().getName();
                Log.d("ATW","externalFilesDir+fileName:"+externalFilesDir+path);
                Log.d("ATW","path:"+path);

                RequestBody fileBody = RequestBody
                        .create(MediaType.parse("application/octet-stream"), loadpickfile.getFile());/*application/octet-stream*/
                MultipartBody.Builder builder = new MultipartBody.Builder();
                /*String userName = map.get("userName");
                String goodId = map.get("goodId");
                if(userName!=null&&!userName.isEmpty())
                    builder.addFormDataPart("userName", userName);
                if(goodId!=null&&!goodId.isEmpty())
                    builder.addFormDataPart("goodId", goodId);*/
                RequestBody requestBody = builder
                        .setType(MultipartBody.FORM)
                        .addFormDataPart("file", filename, fileBody)
                        .build();
                Request request = new Request.Builder()
                        .url(url)
                        .post(requestBody)
                        .build();
                client.newCall(request).execute();
                Log.d("ATW","client.newCall(request).execute();"+client.newCall(request).execute().toString());
                return client.newCall(request).execute().toString();
            } catch (Exception e){
                return e.toString();
            }
        //}).start();

    }

    /*//向服务器上传用户头像
    public static void uploadUserImg(String userName, String imgPath){
        Map<String, String> map = new HashMap<>();
        map.put("fileName", imgPath);
        map.put("userName", userName);
        uploadFile(map);
    }*/

    //向服务器上传商品图片
   /* public static String uploadGoodImg(String imgPath,){
        Map<String, String> map = new HashMap<>();
        map.put("file", imgPath);

        return uploadFile(map);
    }*/
    //添加新的货物
    public static String uploadFilelist(Map<String, String> map, List<LoadFileVo> loadpickfilelist){
        String userid = map.get("userid");

        // new Thread(() -> {
        try {
            String url = "http://192.168.137.1:8080/good/uploadgoodimg";

            MultipartBody.Builder builder = new MultipartBody.Builder();
            for (int i=1;i<loadpickfilelist.size();i++){
                RequestBody fileBody = RequestBody
                        .create(MediaType.parse("application/octet-stream"), loadpickfilelist.get(i).getFile());
                builder.addFormDataPart("file",loadpickfilelist.get(i).getFile().getName(),fileBody);
                Log.d("ATL","loadpickfilelist.get(i).getFile().exists():"+loadpickfilelist.get(i).getFile().exists());
            }
            builder.addFormDataPart("userid",userid);
            builder.addFormDataPart("goodname",map.get("goodname"));
            builder.addFormDataPart("goodexpression",map.get("goodexpression"));
            builder.addFormDataPart("goodprice",map.get("goodprice"));
            Log.d("ATL","userid:"+userid);
            MultipartBody requestBody = builder.build();
            //构建请求
            Request request = new Request.Builder().url(url)// 地址
             .post(requestBody)//添加请求
            .build();

            /*client.newCall(request).enqueue(new Callback() {//关于上传成功的函数
                @Override
                public void onFailure(Call call, IOException e) {

                    System.out.println("上传失败:e.getLocalizedMessage() = " + e.getLocalizedMessage());
                }

                @Override
                public void onResponse(Call call, Response response) throws IOException {

                    /*Looper.prepare();
                    Toast.makeText(MainActivity.this, "用户名或密码错误", Toast.LENGTH_SHORT).show();
                    Looper.loop();


                }
            });*/
            ResponseBody responsebody=client.newCall(request).execute().body();


            //Log.d("ATP", "result1):"+list.toString());
            return responsebody.string();
        } catch (Exception e){
            return null;
        }
        //}).start();

    }
}