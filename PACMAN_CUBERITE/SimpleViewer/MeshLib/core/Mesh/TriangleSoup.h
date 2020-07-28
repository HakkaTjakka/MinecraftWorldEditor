#ifndef _TRIANGLE_SOUP_H_
#define _TRIANGLE_SOUP_H_

#include <vector>
#include <map>
#include <string.h>
#include <iostream>
#include <fstream>

#include "../Geometry/Point.h"
#include "../Geometry/Point2.h"
#include "../Parser/parser.h"
#include "../Parser/StrUtil.h"

namespace MeshLib
{
namespace TriangleSoup
{

class CVertex
{
	public:
		CPoint    m_point;
		CPoint2   m_uv;
		CPoint    m_rgb;
		CPoint    m_normal;
		int       m_id;
		double    m_area;
};

class CFace
{
	public:
		int m_id;
		CVertex * m_v[3];
		CPoint    m_normal;
		double    m_area;
};



class CTriangleMesh
{
  public:

	CTriangleMesh()
	{
		m_has_uv     = false;
		m_has_rgb    = false;
		m_has_normal = false;
	};

	~CTriangleMesh(){
		for( size_t i = 0; i < m_vertices.size(); i ++ )
		{
			CVertex * pV = m_vertices[i];
			delete pV;
		}
		for( size_t i = 0; i < m_faces.size(); i ++ )
		{
			CFace * pF = m_faces[i];
			delete pF;
		}
		m_vertices.clear();
		m_faces.clear();
	};
	
	bool m_has_uv;
	bool m_has_rgb;
	bool m_has_normal;


	std::vector<CFace*> 	& faces() { return	m_faces;};
	std::vector<CVertex*> 	& vertices() { return	m_vertices;};

   protected:

	std::vector<CVertex*>   m_vertices;
	std::vector<CFace*> 	m_faces;
	std::map<int,CVertex*>  m_map;

   public:

	void read_vertex_m( char * line )
	{
		char * str = strtok(line, " \r\n");
		if( strcmp( str, "Vertex" ) != 0 )
		{
			std::cerr << "Error in reading vertex" << std::endl;
			return;
		}
		CVertex * pV = new CVertex;
        	pV->m_rgb = CPoint(1,1,1);

		str = strtok(NULL, " \r\n");

		pV->m_id = atoi( str );

		CPoint p;
		for( int i = 0; i < 3; i ++ )
		{
			str = strtok(NULL, " \r\n");
			p[i] = atof( str );
		}
		pV->m_point = p;

		str = strtok( NULL, "\r\n" );

		if( str == NULL ) return;

		std::string s(str);

		size_t pos0 = s.find_first_of('{');
		size_t pos1 = s.find_last_not_of('}');

		s = s.substr( pos0+1, pos1);

		CParser parser(s);

		for( std::list<CToken*>::iterator iter = parser.tokens().begin(); iter != parser.tokens().end(); iter ++ )
		{
			CToken * pT = *iter;
			if( pT->m_key == "rgb" )
			{
			   CPoint rgb;
			   sscanf(pT->m_value.c_str(), "(%lf %lf %lf)", &rgb[0], &rgb[1], &rgb[2]);
			   pV->m_rgb = rgb;
			   m_has_rgb = true;
			}
			if( pT->m_key == "uv" )
			{
			   CPoint2 uv;
			   sscanf(pT->m_value.c_str(), "(%lf %lf)", &uv[0], &uv[1]);
			   pV->m_uv = uv;
			   m_has_uv = true;
			}
		}

		m_vertices.push_back( pV );
		m_map[pV->m_id] = pV;
	};

	void read_face_m( char * line )
	{
		char * str = strtok(line, " \r\n");
		if( strcmp( str, "Face" ) != 0 )
		{
			std::cerr << "Error in reading face" << std::endl;
			return;
		}
		CFace * pF = new CFace;

		str = strtok(NULL, " \r\n");
		pF->m_id = atoi( str );

		for( int i = 0; i < 3; i ++ )
		{
			str = strtok(NULL, " \r\n");
			int id = atoi( str );
			//pF->m_v[i] = m_vertices[id-1];
			pF->m_v[i] = m_map[id];
		}
		m_faces.push_back( pF );
	};

	void read_m( const char * name )
	{
		FILE * fp=fopen(name,"r");
		char line[1024];

		while( !feof( fp ) )
		{
			if( fgets(line, 1024, fp) == NULL ) break;

			if( strncmp( line, "Vertex", 6 ) == 0 )
			{
				read_vertex_m(line);
				continue;
			}
			if( strncmp( line, "Face", 4 ) == 0 )
			{
				read_face_m(line);
				continue;
			}
		}
		fclose( fp );
	}
};

class CObjVertex
{
public:
	int m_ipt;
	int m_iuv;
	int m_inl;
};

class CObjFace
{
public:
	CObjVertex m_v[3];
	double m_area;
	CPoint m_normal;
};

class CObject
{
public:
	CObject() 
	{ 
		m_has_uv = false;
		m_has_normal = false;
	}
	
	void read( const char * input );

	std::vector<CPoint>  & points()  { return m_points;  };
	std::vector<CPoint2> & uvs()     { return m_uvs;     };
	std::vector<CPoint>  & normals() { return m_normals; };
	std::vector<CObjFace> & faces()  { return m_faces;   };
protected:

	std::vector<CPoint>   m_points;
	std::vector<CPoint2>  m_uvs;
	std::vector<CPoint>   m_normals;

	std::vector<CObjFace> m_faces;

public:

	bool m_has_uv;
	bool m_has_normal;
};

void CObject::read( const char * input )
{
	FILE * fp;
	
	fp = fopen( input,"r" );

	while( !feof(fp) )
	{
		char line[1024];
		if( fgets(line,1024,fp) == NULL ) return;


		if( line[0] == 'v' )
		{

			if( line[1]=='t' )
			{
				CPoint2 uv;
				sscanf(line,"vt %lf %lf", &uv[0], &uv[1]);
				m_uvs.push_back( uv );
				continue;
			}
			
			if( line[1] == 'n')
			{
				CPoint n;
				sscanf(line,"vn %lf %lf %lf", &n[0], &n[1], &n[2]);
				m_normals.push_back( n );
				continue;
			}

			CPoint p;
			sscanf(line,"v %lf %lf %lf", &p[0], &p[1], &p[2]);
			m_points.push_back( p );
			continue;
		}

		if( line[0] == 'f' )
		{
			CObjFace pf;
			
			char * str = strtok( line, " \n" );

			int ids[9];
			int count = 0;

			while( str = strtok(NULL, " /\n") )
			{
				ids[count++] = atoi( str ) - 1;
			}
		
			int c = count/3;

			for( int i = 0; i < 3 ; i ++ )
			{
				pf.m_v[i].m_ipt = ids[i*c+0];
			}

			if( count > 1 )
			{
				m_has_uv = true;
				for( int i = 0; i < 3 ; i ++ )
				{
					pf.m_v[i].m_iuv = ids[i*c+1];
				}
			}

			if( count == 3 )
			{
				m_has_normal = true;
				for( int i = 0; i < 3 ; i ++ )
				{
					pf.m_v[i].m_inl = ids[i*c+2];
				}
			}

			m_faces.push_back(pf);
		}		

	}

}


}
}
#endif


/* std::string version is slow

void CObject::read( const char * input )
{
	std::ifstream file( input );

	std::string line;

	while( std::getline( file, line ) )
	{
		strutil::Tokenizer TK(line);

		if( !TK.nextToken() ) continue;
		std::string key = TK.getToken();

		if( key == "v" )
		{
			CPoint p;
			for(int i = 0; i < 3; i ++ )
			{
				TK.nextToken(" \n");
				p[i] = strutil::parseString<double>( TK.getToken() );
			}
			m_points.push_back( p );
			continue;
		}

		if( key == "vt" )
		{
			CPoint2 uv;
			for(int i = 0; i < 2; i ++ )
			{
				TK.nextToken(" \n");
				uv[i] = strutil::parseString<double>( TK.getToken() );
			}
			m_uvs.push_back( uv );
			continue;
		}

		if( key == "vn" )
		{
			CPoint n;
			for(int i = 0; i < 3; i ++ )
			{
				TK.nextToken(" \n");
				n[i] = strutil::parseString<double>( TK.getToken() );
			}
			m_normals.push_back( n );
			continue;
		}

		if( key == "f" )
		{
			CObjFace pf;
			for( int i = 0; i < 3; i ++ )
			{
				TK.nextToken(" \n");			
				strutil::Tokenizer STK( TK.getToken(), "/ \n" );

				STK.nextToken();
				pf.m_v[i].m_ipt = strutil::parseString<int>( STK.getToken() )-1;

				if( STK.nextToken() )
				{
					pf.m_v[i].m_iuv = strutil::parseString<int>( STK.getToken() )-1;
					m_has_uv = true;
				}

				if( STK.nextToken() )
				{
					pf.m_v[i].m_inl = strutil::parseString<int>( STK.getToken() )-1;
					m_has_normal = true;
				}
			}
			m_faces.push_back(pf);
		}
		

	}

}
*/
