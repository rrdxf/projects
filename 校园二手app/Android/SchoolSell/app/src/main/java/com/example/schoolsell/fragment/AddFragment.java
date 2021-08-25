package com.example.schoolsell.fragment;

import android.Manifest;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Looper;
import android.provider.MediaStore;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.core.content.FileProvider;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.adapter.LoadPicAdapter;
import com.example.schoolsell.beans.Good;
import com.example.schoolsell.beans.GoodandImage;
import com.example.schoolsell.beans.User;
import com.example.schoolsell.connect.HttpUtil;
import com.example.schoolsell.connect.JSONUtil;
import com.example.schoolsell.entity.LoadFileVo;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

public class AddFragment extends Fragment {

    private AddViewModel mViewModel;
    private EditText sendgood_et_goodname=null;
    private EditText sendgood_et_goodexpress=null;

    private RecyclerView sendgood_imbtn_addimg=null;
    private Button add_btn_adgood=null;
    private EditText add_et_addprice=null;
    private RecyclerView rvPic=null;
    private TextView tvNum=null;



    //上传图片的定义
    private List<LoadFileVo>fileList=new ArrayList<>();;
    private LoadPicAdapter adapter=null;

    private String mPhotoPath=null;
    private Uri uriImage;
    File mPhotoFile=null;

    View view=null;




    public static AddFragment newInstance() {
        return new AddFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {



        view=inflater.inflate(R.layout.activity_send_good, container, false);
        sendgood_et_goodexpress=view.findViewById(R.id.sendgood_et_goodexpress);
        sendgood_et_goodname=view.findViewById(R.id.sendgood_et_goodname);
        sendgood_imbtn_addimg=view.findViewById(R.id.sendgood_imbtn_addimg);
        add_btn_adgood=view.findViewById(R.id.add_btn_adgood);
        add_et_addprice=view.findViewById(R.id.add_et_addprice);

        return view;
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(AddViewModel.class);
        MyApplication application = (MyApplication)this.getActivity().getApplication();
        initAdapter();
        initbtnandetlisener(application);
    }

    private void initbtnandetlisener(MyApplication application) {

        add_btn_adgood.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //initAdapter();
                new Thread(() -> {
                    String userid=application.getUser().getUserid();

                    String goodprice=add_et_addprice.getText().toString();
                    String goodexpression=sendgood_et_goodexpress.getText().toString();
                    String goodname=sendgood_et_goodname.getText().toString();



                    if (goodprice!=null&&goodexpression!=null&&goodname!=null) {
                        add_et_addprice.setText("");
                        sendgood_et_goodname.setText("");
                        sendgood_et_goodexpress.setText("");

                        HashMap<String, String> map = new HashMap<>();
                        map.put("userid", userid);
                        map.put("goodprice", goodprice);
                        map.put("goodexpression", goodexpression);
                        map.put("goodname", goodname);


                        String upimgresult = HttpUtil.uploadFilelist(map, fileList);

                        GoodandImage goodandImage= JSONUtil.fromJson(upimgresult,GoodandImage.class);

                        //Log.d("II", "imagelist:"+imagelist.toString());
                        application.getGoods().add(new Good(goodandImage.getGoodid(),goodname,goodprice,goodexpression,userid, goodandImage.getImagelist(), new User(userid, application.getUser().getUsername(),"icon_"+userid+".jpg")));
                        for (int i=1;i<fileList.size();i++){
                            fileList.remove(i);
                        }
                        Log.d("ATP", "application.getGoods():"+application.getGoods().toString());
                        if (upimgresult!=null){
                            Looper.prepare();
                            Toast.makeText(getContext(), "上传物品成功！", Toast.LENGTH_SHORT).show();
                            Looper.loop();
                        }else
                        {
                            Looper.prepare();
                            Toast.makeText(getContext(), "上传物品失败！", Toast.LENGTH_SHORT).show();
                            Looper.loop();
                        }

                        Log.d("ATF", "upimgresult:" + upimgresult);
                    }else {
                        Looper.prepare();
                        Toast.makeText(getContext(), "请输入完整的货物信息！", Toast.LENGTH_SHORT).show();
                        Looper.loop();
                    }
                //Log.d("ATF","fileList:"+fileList.get(1).getFile().getName());
                }).start();


            }

        });

    }


    private void initAdapter(){
        if (fileList.size()==0)
            fileList.add(new LoadFileVo());
        adapter=new LoadPicAdapter(this.getActivity(),fileList);
        sendgood_imbtn_addimg.setAdapter(adapter);
        sendgood_imbtn_addimg.setLayoutManager(new GridLayoutManager(this.getActivity(),3));
        adapter.setListener((new LoadPicAdapter.OnItemClickListener() {
            @Override
            public void click(View view, int positon) {
                Log.d("ATF", "fileList.size():" +fileList.size());
                if (fileList.size()>3){
                    Looper.prepare();
                    Toast.makeText(getContext(), "最多上传3个图片", Toast.LENGTH_SHORT).show();
                    Looper.loop();
                }else {
                    selectPic();
                }
            }

            @Override
            public void del(View view) {

            }
        }));
    }

    //选择图片
    private void selectPic(){
        if (ContextCompat.checkSelfPermission(this.getActivity(),Manifest.permission.CAMERA)!= PackageManager.PERMISSION_GRANTED
                || ContextCompat.checkSelfPermission(this.getActivity(), Manifest.permission.READ_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED || ContextCompat.checkSelfPermission(this.getActivity(), Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED){
            Log.d("ATF", "===========================================");
            ActivityCompat.requestPermissions(this.getActivity(),
                    new String[]{Manifest.permission.CAMERA,
                            Manifest.permission.READ_EXTERNAL_STORAGE,
                            Manifest.permission.WRITE_EXTERNAL_STORAGE},1);
        }
        final  CharSequence[] items={"相册","拍照"};
        AlertDialog.Builder dig=new AlertDialog.Builder(this.getActivity());
        dig.setTitle("添加图片");
        dig.setItems(items, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                if (which==0){
                    Log.d("ATF", "点击的相册");
                    Intent intent=new Intent(Intent.ACTION_PICK);
                    intent.setType("image/*");
                    startActivityForResult(intent, 0);

                    //intent.getData();

                }else {
                    Log.d("ATF", "点击相机");
                    try{
                        Intent intent=new Intent("android.media.action.IMAGE_CAPTURE");
                        startActivityForResult(intent, 1);
                        mPhotoPath=getSDPath()+"/"+getPhotoFileName();
                        Log.d("ATF", "mPhotoPath:" +mPhotoPath);
                        mPhotoFile=new File(mPhotoPath);
                        if (!mPhotoFile.exists()){
                            mPhotoFile.createNewFile();
                        }
                        uriImage= FileProvider.getUriForFile(getContext(),"com.example.schoolsell",mPhotoFile);
                        Log.d("ATF", "uriImage:" +uriImage);
                        //uriImage = FileProvider.getUriForFile(getContext(), getPackageName() + ".provider", createImageFile());
                        //解决相机兼容问题
                        intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
                        intent.putExtra(MediaStore.EXTRA_OUTPUT,uriImage);
                        startActivityForResult(intent,1);

                    }catch (Exception e){
                        e.printStackTrace();
                    }
                }
            }
        }).create();
        dig.show();
    }
    public String getSDPath(){
        File sdDir=null;
        boolean sdCardExsit=Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED);
        if (sdCardExsit){
            sdDir=Environment.getExternalStorageDirectory();

        }
        return sdDir.toString();
    }
    private String getPhotoFileName(){
        Date date=new Date(System.currentTimeMillis());
        SimpleDateFormat dateFormat=new SimpleDateFormat("'IMG'_yyyyMMdd_HHmmss");
        return dateFormat.format(date)+".jpg";
    }


    @Override
    public void onActivityResult(int requestCode, int resultCode, @Nullable Intent data){
        super.onActivityResult(requestCode, resultCode, data);
         if (requestCode == 1) {
             BitmapFactory.Options options = new BitmapFactory.Options();
             options.inSampleSize = 2; //图片宽高都为原来的二分之一，即图片为原来的四分之一
             Bitmap bitmap = BitmapFactory.decodeFile(mPhotoPath, options);
             if (bitmap != null) {
                 if (uriImage != null) {
                     saveUritoFile(uriImage,1);
                 }

                 if (!bitmap.isRecycled()) {
                     bitmap.recycle(); //回收图片所占的内存
                     System.gc(); //提醒系统及时回收
                 }
             }
         }
         if (requestCode == 0) {

             if (data != null) {

                 Uri uri = data.getData();

                 saveUritoFile(uri,0);
             }
         }

     }

 //将Uri图片类型转换成File，BitMap类型
 //在界面上显示BitMap图片，以防止内存溢出
 //上传可选择File文件上传

     private void saveUritoFile(Uri uriImage,int type) {
         Bitmap photoBmp = null;

         if (uriImage != null) {
             try {
 //                photoBmp = MediaStore.Images.Media.getBitmap(this.getContentResolver(), uriImage);
 //                ByteArrayOutputStream fos = new ByteArrayOutputStream();
 //                photoBmp.compress(Bitmap.CompressFormat.JPEG, 80, fos);
                 //以上代码压缩不行，还是会造成内存溢出

                 BitmapFactory.Options options = new BitmapFactory.Options();
                 options.inSampleSize = 2; //图片宽高都为原来的二分之一，即图片为原来的四分之一
                 photoBmp = BitmapFactory.decodeStream(this.getActivity().getContentResolver()
                         .openInputStream(uriImage), null, options);

                 File file = new File("");
                 if (type==0){
                    String imguri=uriImage.toString();
                    int startIndex = imguri.toString().lastIndexOf('/');
                    String fileName = imguri.toString().substring(startIndex + 1);
                     Log.d("ATU","fileName :"+fileName );
                    file = new File(fileName.replaceAll("%2F", "/"));
                    Log.d("ATU","file.exists():"+file.exists());
                 }else {
                     if (mPhotoFile!=null){
                         file = mPhotoFile;
                     }

                 }
                 if (file!=null)
                    fileList.add(new LoadFileVo(file,0 , false, photoBmp));

                 if (fileList.size()>3){    //判断时候达到最大数量，如果达到最大数量，则去掉前面的加号
                     fileList.remove(0);
                 }

                 adapter.notifyDataSetChanged();

                } catch (IOException e) {
                e.printStackTrace();

             }

         }
    }
}
