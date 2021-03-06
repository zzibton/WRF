      FUNCTION SKEWT_TSA(OS, P)
C  TSA AND OS(KELVIN),P(MILLIBARS)
C  SIGN(A,B) REPLACES THE ALGEBRAIC SIGN OF A WITH THE SIGN OF B
          A = OS
          TQ = 253.16
          D = 120
          DO 1  I = 1,12
             D = D/2.
C  IF THE TEMPERATURE DIFFERENCE,X, IS SMALL,EXIT THIS LOOP
             X=A*EXP(-2.6518986*SKEWT_W(TQ,P)/TQ)-TQ*((1000./P)**.286)
             IF(ABS(X).LT.0.01)GO TO 2
             TQ = TQ + SIGN(D,X)
  1       CONTINUE
  2   SKEWT_TSA=TQ
      RETURN
      END
