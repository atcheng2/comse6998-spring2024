#include<CDC8600.hh>
#include<assert.h>

namespace CDC8600
{
   namespace instructions
   {   
        bool jmpz
	(
	    uint8_t Xj
	)
	{
	    assert(Xj < 16);
	    if (0 == PROC.X(Xj).u()) return true;
	    else return false;
	}

	bool jmpp
	(
	    uint8_t Xj
	)
	{
	    assert(Xj < 16);
            if (PROC.X(Xj).i() > 0)
                return true;
            return false;
	}
	
        void xkj
	(
	    uint8_t Xj, 
	    uint8_t k
	)
	{
	    assert(Xj < 16);
	    assert(k < 16);
	    PROC.X(Xj).u() = k;
	}

        void rdjki
	(
	    uint8_t Xi, 
	    uint8_t Xj, 
	    uint8_t Xk
	)
	{
	    assert(Xi < 16);
	    assert(Xj < 16);
	    assert(Xk < 16);

            // Consider addr_offset as a 20-bit offset
            i64 addr_offset = 0xfffff & (PROC.X(Xj).i() + PROC.X(Xk).i());
            if (addr_offset >= PROC.FL().u()*256) {
                /* Bad case */
                PROC._XA = PROC.XA().u();
                PROC.cond()(2) = true;
            } else {
                /* Good case */
                PROC.X(Xi).u() = MEM[PROC.RA().u()*256 + addr_offset].u();
            }
	}

        void sdjki
	(
	    uint8_t Xi, 
	    uint8_t Xj, 
	    uint8_t Xk
	)
	{
	    assert(Xi < 16);
	    assert(Xj < 16);
	    assert(Xk < 16);
            i64 addr_offset = PROC.X(Xj).i() + PROC.X(Xk).i();
            if (addr_offset >= PROC.FL().u()*256 || addr_offset < 0) {
                /* Bad case */
                PROC._XA = PROC.XA().u();
                PROC.cond()(2) = true;
            } else {
                /* Good case */
                MEM[PROC.RA().u()*256 + addr_offset].u() = PROC.X(Xi).u();
            }
	}

        void isjki
	(
	    uint8_t Xi, 
	    uint8_t Xj, 
	    uint8_t Xk
	)
	{
	    assert(Xi < 16);
	    assert(Xj < 16);
	    assert(Xk < 16);
            // One's complement - need to keep track of carry
            u64 carry = 0xffffffffffffffff - PROC.X(Xj).u() < PROC.X(Xk).u() ? 1 : 0;
            PROC.X(Xi).u() = PROC.X(Xj).u() + PROC.X(Xk).u() + carry;
	}
	
        void idjkj
	(
	    uint8_t Xj, 
	    uint8_t k
	)
	{
	    assert(Xj < 16);
	    assert(k < 16);
            PROC.X(Xj).i() = PROC.X(Xj).i() - k;
	}

	void idzkj
	(
	   uint8_t Xj,
	   uint8_t Xk
	)
	{
	    assert(Xj < 16);
	    assert(Xk < 16);
            PROC.X(Xj).i() = -PROC.X(Xk).i();
	}

	void isjkj
	(
	    uint8_t Xj,
	    uint8_t k
	)
	{
	    assert(Xj < 16);
	    assert(k < 16);
            PROC.X(Xj).i() = PROC.X(Xj).i() + k;
	}

	void ipjkj
	(
	    uint8_t Xj,
	    uint8_t Xk
	)
	{
	    assert(Xj < 16);
	    assert(Xk < 16);

            PROC.X(Xj).i() = ((long long) -1) & (PROC.X(Xj).i() * PROC.X(Xk).i());
	}

	void rdKj
	(
	    uint8_t Xj,
	    uint32_t K
	)
	{
	    assert(Xj < 16);
	    assert(K < 1024*1024);

	    if (K < PROC.FL().u()*256)
	    {
		// Good
		uint32_t addr = PROC.RA().u()*256 + K;	// Architected address
		assert(addr < params::MEM::N);		// Check against hardware limit
		PROC.X(Xj) = MEM[addr];
	    }
	    else
	    {
		// Bad
		PROC.cond()(2) = true;
		PROC._XA = PROC.XA().u();
	    }
	}

   } // namespace instructions
} // namespace CDC8600
