

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class Myapp
 */
@WebServlet("/Myapp")
public class Myapp extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Myapp() {
        super();
        // TODO Auto-generated constructor stub
    }

    
    /**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	Connection conn = null;
	ResultSet rs=null;
    Statement stmt = null;
    final String DB_URL="jdbc:mysql://localhost/test";
    final String USER = "root";
    final String PASS = "root";
protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

	
	 // Set response content type
    response.setContentType("text/html");
    PrintWriter out = response.getWriter();
   String title = "Database Result";
    String docType =
      "<!doctype html public \"-//w3c//dtd html 4.0 " +
       "transitional//en\">\n";
       out.println(docType +
       "<html>\n" +
       "<head><title>" + title + "</title></head>\n" +
       "<body bgcolor=\"#f0f0f0\">\n" +
       "<h1 align=\"center\">" + title + "</h1>\n");


	String name=request.getParameter("name");
	String rollno=request.getParameter("rollno");
	String dob=request.getParameter("DOB");

	
	try {
	     Class.forName("com.mysql.jdbc.Driver");
	     conn = DriverManager.getConnection(DB_URL,USER,PASS);
	     stmt = conn.createStatement();
	     String qry="insert into student_details values(?,?,?)";
	     PreparedStatement preparedStmt = conn.prepareStatement(qry);
	     preparedStmt.setString (1,name);
	     preparedStmt.setString (2,rollno);
	     preparedStmt.setString (3,dob);
	     preparedStmt.execute();
	     
	     
	     conn.close();
	     
	     
	     
	 } catch (SQLException e) {
	     throw new ServletException("Servlet Could not display records.", e);

	 } catch (ClassNotFoundException e) {
	     throw new ServletException("JDBC Driver not found.", e);

	 }
	}



    
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
		doGet(request,response);

	      // Set response content type
	      response.setContentType("text/html");
	      PrintWriter out = response.getWriter();
/*	      String title = "Database Result";
	      String docType =
	        "<!doctype html public \"-//w3c//dtd html 4.0 " +
	         "transitional//en\">\n";
	         out.println(docType +
	         "<html>\n" +
	         "<head><title>" + title + "</title></head>\n" +
	         "<body bgcolor=\"#f0f0f0\">\n" +
	         "<h1 align=\"center\">" + title + "</h1>\n");*/
	      try{
	         // Register JDBC driver
	         Class.forName("com.mysql.jdbc.Driver");

	         // Open a connection
	         conn = DriverManager.getConnection(DB_URL,USER,PASS);

	         // Execute SQL query
	         stmt = conn.createStatement();
	         String sql;
	         sql = "select name,rollno,DOB from student_details";
	         ResultSet rs = stmt.executeQuery(sql);

	         // Extract data from result set
	         while(rs.next()){
	            //Retrieve by column name
	            
	            
	            String name = rs.getString("name");
	            String rollno = rs.getString("rollno");
	            String DOB = rs.getString("DOB");


	            //Display values
	            
	            out.println(", Name: " + name + "<br>");
	            out.println(", Roll no: " + rollno + "<br>");
	            out.println(", Date of birth: " + DOB + "<br>");
	            out.println("<br>");
	         }
	         out.println("</body></html>");

	         // Clean-up environment
	         rs.close();
	         stmt.close();
	         conn.close();
	      }catch(SQLException se){
	         //Handle errors for JDBC
	         se.printStackTrace();
	      }catch(Exception e){
	         //Handle errors for Class.forName
	         e.printStackTrace();
	      }finally{
	         //finally block used to close resources
	         try{
	            if(stmt!=null)
	               stmt.close();
	         }catch(SQLException se2){
	         }// nothing we can do
	         try{
	            if(conn!=null)
	            conn.close();
	         }catch(SQLException se){
	            se.printStackTrace();
	         }//end finally try
	      } //end try
	   }
	} 
