/*
 * Final Sistemas Operativos.
 * Cliente en java
 * 
 * compilacion:		javac Cliente.java
 * 
 * ejecucion:		java Cliente localhost
 * 
 * * 
 * Michael Duarte 	09490247
 * Hector Garcia	09490255
 * 
 */
import java.awt.BorderLayout;
import java.io.*;
import java.net.*;
import javax.swing.*;
import java.awt.Font;
import java.awt.event.*;

class Cliente extends JFrame{
	
	static DataOutputStream out = null;
	static DataInputStream in = null;
	String NumeroControl, Carrera, Nombre;
	static byte[] arr;
	static Socket socket = null;
	int numBytes;
	static String Host = "";
	
	public Cliente(String t)
	{
		super(t);
		//this.setSize(306, 148);
		this.setSize(348,165);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		getContentPane().setLayout(null);
		
		       JTabbedPane panelConFichas = new JTabbedPane();
		       panelConFichas.setBounds(0, 0, 346, 158);
		       
		       JLabel etiqueta1 = new JLabel( "panel uno", SwingConstants.CENTER );
		       JPanel panel1 = new JPanel();
		       panel1.setLayout(null);  
		       panel1.add( etiqueta1 ); 
		       panelConFichas.addTab( "Altas", null, panel1, "Primer panel" ); 
		            
		       JLabel lblNoControl = new JLabel("No. Control:");
		       lblNoControl.setBounds(10, 11, 66, 14);
		       panel1.add(lblNoControl);
		             
		       textField = new JTextField();
		       textField.setBounds(86, 8, 132, 20);
		       panel1.add(textField);
		       textField.setColumns(10);
		            
		       JLabel lblNombre = new JLabel("Nombre:");
		       lblNombre.setBounds(10, 36, 66, 14);
		       panel1.add(lblNombre);
		            
		       textField_1 = new JTextField();
		       textField_1.setBounds(86, 33, 132, 20);
		       panel1.add(textField_1);
		       textField_1.setColumns(10);
		            
		       final JComboBox comboBox = new JComboBox();
		       comboBox.setBounds(10, 67, 208, 20);
		       comboBox.setBounds(10, 67, 208, 20);
		       comboBox.addItem("Ing. en Sistemas Computacionales");
		       comboBox.addItem("Ing. Quimica");
		       comboBox.addItem("Lic. en Contaduria");
		       comboBox.addItem("Ing. Industrial");
		   	   comboBox.addItem("Ing. Electrica");
		       comboBox.addItem("Ing. Electronica");
		       comboBox.addItem("Ing. Mecanica");
		       comboBox.addItem("Ing. Mecatronica");
		   	   comboBox.addItem("Ing. Informatica");
		       comboBox.addItem("Ing. en Logistica");
		       comboBox.addItem("Ing. en Gestion Empresarial");
			comboBox.addItem("Ing. en Energias Renovables");
		       panel1.add(comboBox);
		       
		       JButton btnGuardar = new JButton("Alta");
		       btnGuardar.addMouseListener(new MouseAdapter() 
		       {
		       	@Override
		       	public void mouseClicked(MouseEvent arg0) 
		       	{			
		       		
		       		NumeroControl = textField.getText();
		       		Nombre = textField_1.getText();
		       		Object e = comboBox.getSelectedItem();
		       		Carrera = String.valueOf(e);
		       		String text = NumeroControl+"&"+Nombre+"&"+Carrera+"a";
				if (NumeroControl.length()==0 || Nombre.length()==0){
					JOptionPane.showMessageDialog(null,"Campos Incompletos");
					return;
				}					
		       		arr = text.getBytes();
				Abrir();
		       		try {
						out.write(arr,0,arr.length);
					} catch (IOException e1) {						
						e1.printStackTrace();
					}
					arr=new byte[1024];//inicializamos nuevo buffer con espacio suficiente
					
					try {
						numBytes=in.read(arr);
					} catch (IOException e1) {						
						e1.printStackTrace();
					}//recibimos
					System.out.println(new String(arr,0,numBytes));
					if("OK".equals(new String(arr,0,numBytes)))
						JOptionPane.showMessageDialog(null,"Transaccion completa \"Alta\"");
					else
						JOptionPane.showMessageDialog(null,new String(arr,5,numBytes));
											
					Cerrar();
					textField.setText("");
					textField_1.setText("");
		       	}		       	
		       });
		       btnGuardar.setBounds(227, 0, 68, 93);
		       panel1.add(btnGuardar);
		       
		       // establecer panel2 y agregarlo al objeto JTabbedPane
		       JLabel etiqueta2 = new JLabel( "panel dos", SwingConstants.CENTER );
		       JPanel panel2 = new JPanel();
		       panel2.setLayout(null);
		       panel2.add( etiqueta2 );
		       panelConFichas.addTab( "Bajas", null, panel2, "Segundo panel" );
		       
		       JLabel lblNoControl_1 = new JLabel("No. Control:");
		       lblNoControl_1.setBounds(10, 36, 65, 14);
		       panel2.add(lblNoControl_1);
		       
		       textField_2 = new JTextField();
		       textField_2.setBounds(77, 33, 135, 20);
		       panel2.add(textField_2);
		       textField_2.setColumns(10);
		       
		       JButton btnNewButton = new JButton("Baja");
		       btnNewButton.addMouseListener(new MouseAdapter() {
		       	@Override
		       	public void mouseClicked(MouseEvent arg0) {
		       		NumeroControl = textField_2.getText();
		       		String text = NumeroControl+"b";
		       		arr = text.getBytes();
				Abrir();
		       		try {
						out.write(arr,0,arr.length);
					} catch (IOException e1) {						
						e1.printStackTrace();
					}
					
					arr=new byte[1024];//inicializamos nuevo buffer con espacio suficiente
					
					try {
						numBytes=in.read(arr);
					} catch (IOException e1) {						
						e1.printStackTrace();
					}//recibimos
					System.out.println(new String(arr,0,numBytes));
					
					if("OK".equals(new String(arr,0,numBytes)))
						JOptionPane.showMessageDialog(null,"Transaccion completa \"Baja\"");
					else
						JOptionPane.showMessageDialog(null,new String(arr,5,numBytes));
					
					Cerrar();
					textField_2.setText("");
		       	}
		       });
		       btnNewButton.setBounds(227, 0, 68, 93);
		       panel2.add(btnNewButton);
		 
		       // establecer panel3 y agregarlo al objeto JTabbedPane
		       JLabel etiqueta3 = new JLabel( "panel tres" );
		       JPanel panel3 = new JPanel();
		       panel3.setLayout(null);  
	           panel3.add( etiqueta3, BorderLayout.CENTER );
		       panelConFichas.addTab( "Modificaciones", null, panel3, "Tercer panel" );
		       
		       JButton btnGuardar_2 = new JButton("Guardar");
		       btnGuardar_2.setBounds(314, 162, 89, 23);
		       panel3.add(btnGuardar_2);
		       
		       JLabel lblNewLabel = new JLabel("No. Control:");
		       lblNewLabel.setBounds(10, 11, 66, 14);
		       panel3.add(lblNewLabel);
		       
		       textField_3 = new JTextField();
		       textField_3.setBounds(86, 8, 132, 20);
		       panel3.add(textField_3);
		       textField_3.setColumns(10);
		       
		       JLabel lblNewLabel_1 = new JLabel("Nombre:");
		       lblNewLabel_1.setBounds(10, 36, 66, 14);
		       panel3.add(lblNewLabel_1);
		       
		       textField_4 = new JTextField();
		       textField_4.setBounds(86, 33, 132, 20);
		       panel3.add(textField_4);
		       textField_4.setColumns(10);
		       
		       final JComboBox comboBox_1 = new JComboBox();
		       comboBox_1.setBounds(10, 67, 208, 20);
		       comboBox_1.addItem("Ing. en Sistemas Computacionales");
		       comboBox_1.addItem("Ing. Quimica");
		       comboBox_1.addItem("Lic. en Contaduria");
		       comboBox_1.addItem("Ing. Industrial");
		   	   comboBox_1.addItem("Ing. Electrica");
		       comboBox_1.addItem("Ing. Electronica");
		       comboBox_1.addItem("Ing. Mecanica");
		       comboBox_1.addItem("Ing. Mecatronica");
		   	   comboBox_1.addItem("Ing. Informatica");
		       comboBox_1.addItem("Ing. en Logistica");
		       comboBox_1.addItem("Ing. en Gestion Empresarial");
		  	   comboBox_1.addItem("Ing. en Energias Renovables");
		       panel3.add(comboBox_1);
		
		       JButton btnNewButton_1 = new JButton("Modificar");
		       btnNewButton_1.setFont(new Font("Tahoma", Font.PLAIN, 8));
		       btnNewButton_1.setBounds(227, 0, 68, 93);		       
		       btnNewButton_1.addMouseListener(new MouseAdapter() {
		       	@Override
		       	public void mouseClicked(MouseEvent arg0) {
		       		NumeroControl = textField_3.getText();
		       		Nombre = textField_4.getText();
		       		Object e = comboBox_1.getSelectedItem();
		       		Carrera = String.valueOf(e);
		       		String text = NumeroControl+"&"+Nombre+"&"+Carrera+"m";
				if (NumeroControl.length()==0 || Nombre.length()==0){
				  JOptionPane.showMessageDialog(null,"Campos Incompletos");
				  return;
				}		
		       		arr = text.getBytes();
				Abrir(); 
		       		try {
						out.write(arr,0,arr.length);
					} catch (IOException e1) {						
						e1.printStackTrace();
					}
					
					arr=new byte[1024];//inicializamos nuevo buffer con espacio suficiente
					
					try {
						numBytes=in.read(arr);
					} catch (IOException e1) {						
						e1.printStackTrace();
					}//recibimos
					System.out.println(new String(arr,0,numBytes));
					
					if("OK".equals(new String(arr,0,numBytes)))
						JOptionPane.showMessageDialog(null,"Transaccion completa \"Modificacion\"");
					else
						JOptionPane.showMessageDialog(null,new String(arr,5,numBytes));
					
					Cerrar();
					textField_3.setText("");
					textField_4.setText("");
		       	}
		       });
		       panel3.add(btnNewButton_1);
		       
		       
		       // establecer panel4 y agregarlo al objeto JTabbedPane
		       JLabel etiqueta4 = new JLabel( "panel tres" );
		       JPanel panel4 = new JPanel();
		       panel4.setLayout(null);
		       panel4.add( etiqueta4 );
		       panelConFichas.addTab( "Consultas", null, panel4, "Cuarto panel" );
		       
		       JLabel lblNoControl_2 = new JLabel("No. Control:");
		       lblNoControl_2.setBounds(10, 11, 66, 14);
		       panel4.add(lblNoControl_2);
		       
		       textField_5 = new JTextField();
		       textField_5.setBounds(86, 8, 132, 20);
		       panel4.add(textField_5);
		       textField_5.setColumns(10);
		       
		       JLabel lblNombre_1 = new JLabel("Nombre:");
		       lblNombre_1.setBounds(10, 36, 66, 14);
		       panel4.add(lblNombre_1);
		       
		       JLabel lblCarrera = new JLabel("Carrera:");
		       lblCarrera.setBounds(10, 61, 66, 14);
		       panel4.add(lblCarrera);
		       
		       final JLabel label = new JLabel("");
		       label.setBounds(86, 39, 132, 14);
		       panel4.add(label);
		       
		       final JLabel label_1 = new JLabel("");
		       label_1.setBounds(86, 61, 132, 14);
		       panel4.add(label_1);
		       
		       JButton btnNewButton_2 = new JButton("Consultar");
		       btnNewButton_2.addMouseListener(new MouseAdapter() {
		       	@Override
		       	public void mouseClicked(MouseEvent arg0) {		
		       		
				NumeroControl = textField_5.getText();
		       		String text = NumeroControl+"c";
		       		arr = text.getBytes();
				Abrir();
		       		try {
						out.write(arr,0,arr.length);
					} catch (IOException e1) {						
						e1.printStackTrace();
					}
					
					arr=new byte[1024];//inicializamos nuevo buffer con espacio suficiente
					
					try {
						numBytes=in.read(arr);
					} catch (IOException e1) {						
						e1.printStackTrace();
					}//recibimos
					System.out.println(new String(arr,0,numBytes));
					
					if((new String(arr,0,numBytes)).contains("ER")){
						JOptionPane.showMessageDialog(null,(new String(arr,5,31)));	
						label.setText("");
						label_1.setText("");
					}
					else
					{
						String vec[] = new String(arr,0,numBytes).split("\t");	
						if(vec.length>1)
						{
						label.setText(vec[1].toString());
						label_1.setText(vec[2].toString());
						}
					}			
					
					Cerrar();
					textField_5.setText("");
		       	}
		       });
		       btnNewButton_2.setFont(new Font("Tahoma", Font.PLAIN, 8));
		       btnNewButton_2.setBounds(227, 0, 68, 93);
		       panel4.add(btnNewButton_2);	       
		       
		JPanel panel = new JPanel();
		panel.setBounds(0, 0, 418, 224);
		getContentPane().add(panel);
		panel.setLayout(null);
		
		panel.add(panelConFichas);
	}

	private static final long serialVersionUID = 1L;
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;
	private JTextField textField_3;
	private JTextField textField_4;
	private JTextField textField_5;

	public void Abrir()
	{
		System.out.println("Solicitando conexion a " + Host);
		try {
			socket = new Socket(Host, 4444);
			out = new DataOutputStream(socket.getOutputStream());
			in = new DataInputStream(socket.getInputStream());	
		} catch (UnknownHostException e) {
			System.err.println("Client: host "+Host+" desconocido\n");
			System.exit(1);
		} catch (IOException e) {
			System.err.println("Client: no fue posible la conexion a "+Host);
			System.exit(1);
		}
	}
	
	public void Cerrar()
	{
		try{
		out.close();
		in.close();
		socket.close();	
		}catch(IOException e){
		  e.printStackTrace();
		}
	}
		
	public static void main(String[] args) throws IOException {
		if (args.length == 0) {
			Host = JOptionPane.showInputDialog(null,"IP del Host");
		}else
			Host = args[0];
		Cliente Obj = new Cliente("Final SO");
		Obj.setVisible(true);
		Obj.setLocationRelativeTo(null);
		//Obj.setResizable(false);
		
	}
}
