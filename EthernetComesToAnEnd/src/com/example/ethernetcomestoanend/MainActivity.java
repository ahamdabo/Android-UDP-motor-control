package com.example.ethernetcomestoanend;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;

/**
 * @author Youssef Nofal
 * @author Ahmed
 * 
 *         This activity is supposed to connect android powered devices to
 *         remote arduino kits connected to ethernet shield with static ip
 *         <SERVERIP> based on UDP.
 * 
 */
public class MainActivity extends Activity {
	public static final String SERVERIP = "192.168.0.40";
	public static final int SERVERPORT = 5000;
	public boolean start;
	public Handler Handler;
	ImageButton on, down, up;
	String message = "";
	boolean bon = false;

	/** Called when the activity is first created. */
	@SuppressLint("HandlerLeak")
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		on = (ImageButton) findViewById(R.id.on);
		down = (ImageButton) findViewById(R.id.down);
		up = (ImageButton) findViewById(R.id.up);
		start = false;
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
		}

		new Thread(new Client()).start();

		Handler = new Handler() {
			@Override
			public void handleMessage(Message msg) {
				// String text = (String) msg.obj;
				// text1.append(text);
			}
		};
	}

	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
		on.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				// on.setBackground(R.drawable.onbutton);
				if (!bon) {
					message = "on";
					start = true;
					Log.i("", "on");
					bon = true;
				} else {
					message = "off";
					start = true;
					Log.i("", "off");
					bon = false;
				}
			}
		});

		down.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub

				message = "left";
				start = true;
				Log.i("", "left");

			}
		});

		up.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				message = "right";
				start = true;
				Log.i("", "right");

			}
		});

	}

	public class Client implements Runnable {
		@Override
		public void run() {

			Log.i("here we go	", " threading");

			while (true) {

				start = false;

				while (start == false) {
				}

				try {
					Thread.sleep(500);
				} catch (InterruptedException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				try {
					InetAddress serverAddr = InetAddress.getByName(SERVERIP);
					// updatetrack("Client: Start connecting\n");
					DatagramSocket socket = new DatagramSocket();
					byte[] buf;
					buf = (message).getBytes();
					DatagramPacket packet = new DatagramPacket(buf, buf.length,
							serverAddr, SERVERPORT);
					// updatetrack("Client: Sending '" + new String(buf) +
					// "'\n");
					socket.send(packet);
					// updatetrack("Client: Message sent\n");
					// updatetrack("Client: Succeed!\n");
					// input.setText("");
					socket.close();
				} catch (Exception e) {
					updatetrack("Client: Error!\n");
				}
			}
		}
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		message = "off";
		start = true;
		Log.i("", "off");
		bon = false;

	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		super.onStop();
		message = "off";
		start = true;
		Log.i("", "off");
		bon = false;

	}

	public void updatetrack(String s) {
		Message msg = new Message();
		String textTochange = s;
		msg.obj = textTochange;
		Handler.sendMessage(msg);
	}

}