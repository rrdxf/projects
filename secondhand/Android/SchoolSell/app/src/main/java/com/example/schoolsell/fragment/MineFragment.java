package com.example.schoolsell.fragment;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.bumptech.glide.Glide;
import com.example.schoolsell.MyApplication;
import com.example.schoolsell.R;
import com.example.schoolsell.connect.container;
import com.makeramen.roundedimageview.RoundedImageView;


public class MineFragment extends Fragment {

    private MineViewModel mViewModel;

    private RoundedImageView mine_info_icon=null;
    private TextView mine_tv_infoname=null;
    private TextView mine_tv_infoid=null;
    private TextView mine_tv_shoucang=null;
    private TextView mine_tv_lishi=null;
    private TextView mine_tv_guanzhu=null;
    private TextView mine_tv_fensi=null;
    private String end="user/uploadicon";
    private TextView loadupimage=null;





    public static MineFragment newInstance() {
        return new MineFragment();
    }
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {



        View view=inflater.inflate(R.layout.activity_mine, container, false);

        loadupimage=view.findViewById(R.id.loadupimage);
        mine_info_icon=view.findViewById(R.id.mine_info_icon);
        mine_tv_infoname=view.findViewById(R.id.mine_tv_infoname);
        mine_tv_infoid=view.findViewById(R.id.mine_tv_infoid);
        mine_tv_shoucang=view.findViewById(R.id.mine_tv_shoucang);
        mine_tv_lishi=view.findViewById(R.id.mine_tv_lishi);
        mine_tv_guanzhu=view.findViewById(R.id.mine_tv_guanzhu);
        mine_tv_fensi=view.findViewById(R.id.mine_tv_fensi);

        return view;
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(MineViewModel.class);
        MyApplication application = (MyApplication)this.getActivity().getApplication();

        //Log.d("WTF","application:"+ application.toString());
        // User user=new User();
        // user=application.getUser();

        String imgurl= container.DOWNLOAD_URL+"icon_"+application.getUser().getUserid()+".jpg";

        if (application.isIslog()==true){
            Log.d("WTF","imgurl:"+imgurl);
            Glide.with(getContext()).load(imgurl).into(mine_info_icon);
        }
        else{
            imgurl=container.DOWNLOAD_URL+"plselog.png";
            Glide.with(getContext()).load(imgurl).into(mine_info_icon);
        }

        mine_tv_infoname.setText(application.getUser().getUsername());
        mine_tv_infoid.setText("账号："+application.getUser().getUserid());

        mine_tv_shoucang.setText("0");
        mine_tv_guanzhu.setText("0");
        mine_tv_lishi.setText("0");
        mine_tv_fensi.setText("0");
        //init();

        // TODO: Use the ViewModel
    }


    //界面初始化数据
    private void init() {

            //获取登录信息中的全局变量
/*
            MyApplication application = ;
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
*/
    }

}
