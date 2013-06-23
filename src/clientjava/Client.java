
package client;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client 
{
    private boolean _running = true;
    private Socket _connection;
    private static PrintStream _out;
    private BufferedReader _in;   
    private String _ip;
    private int _port;
    
    public Client(String pIp, int pPort)
    {
        setIp(pIp);
        setPort(pPort);
    }
    
    
    public void Connect() throws UnknownHostException, IOException
    {
        try 
        {
            _connection = new Socket(getIp(), getPort());
            _out = new PrintStream(_connection.getOutputStream());
            _in = new BufferedReader(new InputStreamReader(new DataInputStream (_connection.getInputStream())));
        } 
        catch(Exception e) 
        {
            System.out.println("No se pudo crear la conexión, la IP dada no tiene ningún servidor ejecutandose.\n"+e);
            System.exit(0);
        }
    } 
    
    public void sendMessage(String pMessage) throws IOException, InterruptedException
    {
        _out.println(pMessage); 
    }
    
    public String readMessage() throws IOException
    {
        String pMessage = "";
        while(_running)
        {
            if(_in.ready())
            {
                pMessage = _in.readLine();
                _running = false;
            }
        }
        _running = true;  
        System.out.println(pMessage);
        return  pMessage;
    }

    public String getIp() 
    {
        return _ip;
    }

    public void setIp(String pIp) 
    {
        this._ip = pIp;
    }

    public int getPort() 
    {
        return _port;
    }

    public void setPort(int pPort) 
    {
        this._port = pPort;
    }
} 

