//--------------------------------------------------------------------------
#ifndef HEPMC_FLOW_H
#define HEPMC_FLOW_H

//////////////////////////////////////////////////////////////////////////
// Matt.Dobbs@Cern.CH, January 2000, refer to:
// M. Dobbs and J.B. Hansen, "The HepMC C++ Monte Carlo Event Record for
// High Energy Physics", Computer Physics Communications (to be published).
//
// particle's flow object
// keeps track of an arbitrary number of flow patterns within a graph 
// (i.e. color flow, charge flow, lepton number flow, ...) 
// Flow patterns are coded with an integer, in the same manner as in Herwig.
// Note: 0 is NOT allowed as code index nor as flow code since it
//       is used to indicate null.
//////////////////////////////////////////////////////////////////////////

// This class can be used to keep track of flow patterns within 
//  a graph. An example is color flow. If we have two quarks going through
//  an s-channel gluon to form two more quarks:
//
//  \q1       /q3   then we can keep track of the color flow with the
//   \_______/      HepMC::Flow class as follows: 
//   /   g   \. 
//  /q2       \q4
//
//  lets say the color flows from q2-->g-->q3  and q1-->g-->q4
//  the individual colors are unimportant, but the flow pattern is.
//  We can capture this flow by assigning the first pattern (q2-->g-->q3)
//  a unique (arbitrary) flow code 678 and the second pattern (q1-->g-->q4)
//  flow code 269.
//  The first two code indices are reserved for color codes, so we store 
//  these codes with the particles as follows:
//    q2->flow().set_icode(1,678);
//    g->flow().set_icode(1,678);
//    q3->flow().set_icode(1,678);
//    q1->flow().set_icode(1,269);
//    g->flow().set_icode(2,269);
//    q4->flow().set_icode(1,269);
//  later on if we wish to know the color partner of q1 we can ask for a list
//  of all particles connected via this code to q1 which do have less than 
//  2 color partners using:
//    set<GenParticle*> result=q1->dangling_connected_partners(q1->icode(1),1,2);
//  this will return a list containing q1 and q4.
//    set<GenParticle*> result=q1->connected_partners(q1->icode(1),1,2);
//  would return a list containing q1, g, and q4.
//

#include <iostream>
#include <map>
#include <set>

namespace HepMC {

    class GenParticle;

    class Flow {

	friend std::ostream& operator<<( std::ostream& ostr, const Flow& f );
	
    public:
	Flow( GenParticle* particle_owner = 0 );
	Flow( const Flow& );
	virtual         ~Flow();
	Flow&           operator=( const Flow& );
	bool            operator==( const Flow& a ) const; //compares only flow
	bool            operator!=( const Flow& a ) const; //patterns not owner

	void            print( std::ostream& ostr = std::cout ) const;

	// returns all connected particles which have "code" in any  of the 
	//  num_indices beginning with index code_index.
	std::set<GenParticle*> connected_partners( int code, int code_index =1,
						   int num_indices = 2 ) const;
	// same as connected_partners, but returns only those particles which
	//  are connected to <=1 other particles (i.e. the flow line "dangles"
	//  at these particles)
	std::set<GenParticle*> dangling_connected_partners( int code, 
			       int code_index = 1, int num_indices = 2 ) const;

	////////////////////
	// access methods //
	////////////////////
	const GenParticle* particle_owner() const;
	int             icode( int code_index = 1 ) const;
	Flow            set_icode( int code_index, int code );

	//////////////////////
	// container access //
	//////////////////////

	bool            empty() const;
	int             size() const;
        void            clear();
	bool            erase( int code_index );

        typedef std::map<int,int>::iterator       iterator;
        typedef std::map<int,int>::const_iterator const_iterator;
        iterator            begin();
        iterator            end();
        const_iterator      begin() const;
        const_iterator      end() const;

    protected: // intended for internal use only
	void            connected_partners( std::set<GenParticle*>* output, 
					    int code,
					    int code_index,
					    int num_indices ) const;
	void            dangling_connected_partners( std::set<GenParticle*>* 
						     output, 
						     std::set<GenParticle*>*
						     visited_particles, 
						     int code, int code_index, 
						     int num_indices ) const; 
    private:
	GenParticle*         m_particle_owner;
	std::map<int,int> m_icode; // stores flow patterns as(code_index,icode)
    };  

    ///////////////////////////
    // INLINE Access Methods //
    ///////////////////////////

    inline const GenParticle* Flow::particle_owner() const {
	return m_particle_owner;
    }
    inline int Flow::icode( int code_index ) const {
	std::map<int,int>::const_iterator a = m_icode.find(code_index);
	return a==m_icode.end() ? 0 : (*a).second;
    }
    inline Flow Flow::set_icode( int code_index, int code ) {
	m_icode[code_index] = code;
	return *this;
    }
    inline bool Flow::empty() const { return (bool)m_icode.empty(); }
    inline int Flow::size() const { return (int)m_icode.size(); }
    inline void Flow::clear() { m_icode.clear(); }
    inline bool Flow::erase( int code_index ) {
	return (bool)m_icode.erase( code_index );
    }
    inline Flow::iterator Flow::begin() { return m_icode.begin(); }
    inline Flow::iterator Flow::end() { return m_icode.end(); }
    inline Flow::const_iterator Flow::begin() const { return m_icode.begin(); }
    inline Flow::const_iterator Flow::end() const { return m_icode.end(); }

    ///////////////////////////
    // INLINE Operators      //
    ///////////////////////////

    inline bool Flow::operator==( const Flow& a ) const {
	// equivalent flows have the same flow codes for all flow_numbers 
	// (i.e. their m_icode maps are identical), but they need not have the
	// same m_particle owner
	return (m_icode == a.m_icode);
    }
    inline bool Flow::operator!=( const Flow& a ) const {
	return !( *this == a );
    }
    inline Flow& Flow::operator=( const Flow& inflow ) {
	// copies only the m_icode ... not the particle_owner
	// this is intuitive behaviour so you can do
	// oneparticle->flow() = otherparticle->flow()
	//
	m_icode = inflow.m_icode;
	return *this;
    }

} // HepMC

#endif  // HEPMC_FLOW_H
//--------------------------------------------------------------------------
