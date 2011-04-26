/**
* @author Cyrille Collette - ccollette@aldebaran-robotics.com
* Aldebaran Robotics (c) 2009 All Rights Reserved
*
*/

#include <almath/tools/altransformhelpers.h>
#include <almath/tools/almathio.h>
#include "../almathtestutils.h"

TEST(ALTransformHelpersTest, normalizeTransform)
{
  float eps = 0.0001f;

  std::vector<AL::Math::Transform> pHList;
  pHList.resize(9);

  for (unsigned int i=0; i<9; i++)
  {
    pHList.at(i) = AL::Math::Transform::from3DRotation(0.2f, 0.3f, 0.4f);
  }

  pHList.at(0).r1_c1 += 0.1f;
  pHList.at(1).r1_c2 += 0.1f;
  pHList.at(2).r1_c3 += 0.1f;

  pHList.at(3).r2_c1 += 0.1f;
  pHList.at(4).r2_c2 += 0.1f;
  pHList.at(5).r2_c3 += 0.1f;

  pHList.at(6).r3_c1 += 0.1f;
  pHList.at(7).r3_c2 += 0.1f;
  pHList.at(8).r3_c3 += 0.1f;

  AL::Math::Transform pHInit;
  AL::Math::Position6D pTmp;
  AL::Math::Transform pHFinal;

  for (unsigned int i=0; i<pHList.size(); i++)
  {
    pHInit = pHList.at(i);

    EXPECT_FALSE(pHInit.isTransform(eps));

    pTmp = AL::Math::Position6DFromTransform(pHInit);
    pHFinal = AL::Math::TransformFromPosition6D(pTmp);

    EXPECT_TRUE(pHFinal.isTransform(eps));
  }
}

TEST(ALTransformHelpersTest, TransformLogarithme)
{
  // ************ TransformLogarithme ************

  // X01
  AL::Math::Transform pMathHIn  = AL::Math::TransformFromRotX(10.0f*TO_RAD);
  AL::Math::Velocity6D pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.1745329f, 0.0f, 0.0f), 1.0e-5f);

  // X02
  pMathHIn  = AL::Math::TransformFromRotX(150.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 2.61799387799149f, 0.0f, 0.0f), 1.0e-5f);

  // X03
  pMathHIn  = AL::Math::TransformFromRotX(179.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 3.12413936106983f, 0.0f, 0.0f), 1.0e-5f);

  // X04
  pMathHIn  = AL::Math::TransformFromRotX(181.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, -3.12413936106983f, 0.0f, 0.0f), 1.0e-5f);

  // X05
  pMathHIn  = AL::Math::TransformFromRotX(-179.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, -3.12413936106983f, 0.0f, 0.0f), 1.0e-5f);

  // X06
  pMathHIn  = AL::Math::TransformFromRotX(-181.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 3.12413936106983f, 0.0f, 0.0f), 1.0e-5f);

  // X07
  pMathHIn  = AL::Math::TransformFromRotX(90.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 1.57079632679490f, 0.0f, 0.0f), 1.0e-5f);

  // X08
  pMathHIn  = AL::Math::TransformFromRotX(10.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.10000000000000f, 0.22567198513826f, 0.28178477701757f, 0.17453292519943f, 0.0f, 0.0f), 1.0e-5f);

  // X09
  pMathHIn  = AL::Math::TransformFromRotX(179.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.10000000000000f, 0.47134729927687f, -0.30832434343239f, 3.12413936106983f, 0.0f, 0.0f), 1.0e-5f);

  // X10
  pMathHIn  = AL::Math::TransformFromRotX(181.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.10000000000000f, -0.46589450904408f, 0.31650352878158f, -3.12413936106983f, 0.0f, 0.0f), 1.0e-5f);

  // X11
  pMathHIn  = AL::Math::TransformFromRotX(179.99f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, +3.14141812066260f, 0.0f, 0.0f), 1.0e-5f); // devrait etre -

  // X12
  pMathHIn  = AL::Math::TransformFromRotX(180.01f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, +3.14141812066260f, 0.0f, 0.0f), 1.0e-5f);

  // X13
  pMathHIn  = AL::Math::TransformFromRotX(180.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 3.14159265358979f, 0.0f, 0.0f), 1.0e-5f);

  // X14
  pMathHIn  = AL::Math::TransformFromRotX(-179.99f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, +3.14141812066260f, 0.0f, 0.0f), 1.0e-5f); // devrait etre -

  // X15
  pMathHIn  = AL::Math::TransformFromRotX(-180.01f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, +3.14141812066260f, 0.0f, 0.0f), 1.0e-5f);

  // X16
  pMathHIn  = AL::Math::TransformFromRotX(-180.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, +3.14159265358979f, 0.0f, 0.0f), 1.0e-5f);

  // X17
  pMathHIn  = AL::Math::TransformFromRotX(+180.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.10000000000000f, +0.47123884392623f, -0.31415928915466f, +3.14159247705847f, 0.0f, 0.0f), 1.0e-5f);

  // X18
  pMathHIn  = AL::Math::TransformFromRotX(+0.1f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.10000000000000f, 0.20026174861823f, 0.29982539092044f, 0.00174532925199f, 0.0f, 0.0f), 1.0e-5f);

  // X19
  pMathHIn  = AL::Math::TransformFromRotX(-0.1f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.10000000000000f, 0.19973814984263f, 0.30017445677084f, -0.00174532925199f, 0.0f, 0.0f), 1.0e-5f);

  // X20
  pMathHIn  = AL::Math::TransformFromRotX(+1.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.10000000000000f, 0.20261291689522f, 0.29824705527385f, 0.01745329251994f, 0.0f, 0.0f), 1.0e-5f);

  // X21
  pMathHIn  = AL::Math::TransformFromRotX(-1.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.10000000000000f, 0.19737692913924f, 0.30173771377784f, -0.01745329251994f, 0.0f, 0.0f), 1.0e-5f);

  // Y01
  pMathHIn  = AL::Math::TransformFromRotY(10.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.1745329f, 0.0f), 1.0e-5f);

  // Y02
  pMathHIn  = AL::Math::TransformFromRotY(150.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 2.61799387799149f, 0.0f), 1.0e-5f);

  // Y03
  pMathHIn  = AL::Math::TransformFromRotY(179.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 3.12413936106983f, 0.0f), 1.0e-5f);

  // Y04
  pMathHIn  = AL::Math::TransformFromRotY(181.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, -3.12413936106983f, 0.0f), 1.0e-5f);

  // Y05
  pMathHIn  = AL::Math::TransformFromRotY(-179.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, -3.12413936106983f, 0.0f), 1.0e-5f);

  // Y06
  pMathHIn  = AL::Math::TransformFromRotY(-181.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 3.12413936106983f, 0.0f), 1.0e-5f);

  // Y07
  pMathHIn  = AL::Math::TransformFromRotY(90.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 1.57079632679490f, 0.0f), 1.0e-5f);

  // Y08
  pMathHIn  = AL::Math::TransformFromRotY(10.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.07356608439926f, 0.20000000000000f, 0.30796471579749f, 0.0f, 0.17453292519943f, 0.0f), 1.0e-5f);

  // Y09
  pMathHIn  = AL::Math::TransformFromRotY(179.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.46725770660228f, 0.20000000000000f, 0.16029656072809f, 0.0f, 3.12413936106983f, 0.0f), 1.0e-5f);

  // Y10
  pMathHIn  = AL::Math::TransformFromRotY(181.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.46998410171867f, 0.20000000000000f, -0.15211737537889f, 0.0f, -3.12413936106983f, 0.0f), 1.0e-5f);

  // Y11
  pMathHIn  = AL::Math::TransformFromRotY(179.99f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, +3.14141812066260f, 0.0f), 1.0e-5f); // devrait etre -

  // Y12
  pMathHIn  = AL::Math::TransformFromRotY(180.01f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, +3.14141812066260f, 0.0f), 1.0e-5f);

  // Y13
  pMathHIn  = AL::Math::TransformFromRotY(180.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 3.14159265358979f, 0.0f), 1.0e-5f);

  // Y14
  pMathHIn  = AL::Math::TransformFromRotY(-179.99f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, +3.14141812066260f, 0.0f), 1.0e-5f); // devrait etre -

  // Y15
  pMathHIn  = AL::Math::TransformFromRotY(-180.01f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, +3.14141812066260f, 0.0f), 1.0e-5f);

  // Y16
  pMathHIn  = AL::Math::TransformFromRotY(-180.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, +3.14159265358979f, 0.0f), 1.0e-5f);

  // Y17
  pMathHIn  = AL::Math::TransformFromRotY(+180.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.47092190248947f, 0.20000000000000f, 0.15803061932648f, 0.0f, 3.14159265358979f, 0.0f), 1.0e-3f);

  // Y18
  pMathHIn  = AL::Math::TransformFromRotY(+0.1f*TO_RAD);
  pMathHIn.r1_c4 = -0.2f;
  pMathHIn.r2_c4 = -0.3f;
  pMathHIn.r3_c4 = -0.1f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.19991268276783f, -0.30000000000000f, -0.10017450754041f, 0.0f, 0.00174532925199f, 0.0f), 1.0e-5f);

  // Y19
  pMathHIn  = AL::Math::TransformFromRotY(-0.1f*TO_RAD);
  pMathHIn.r1_c4 = -0.2f;
  pMathHIn.r2_c4 = -0.3f;
  pMathHIn.r3_c4 = -0.1f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.20008721569303f, -0.30000000000000f, -0.09982544169001f, 0.0f, -0.00174532925199f, 0.0f), 1.0e-5f);

  // Y20
  pMathHIn  = AL::Math::TransformFromRotY(+1.0f*TO_RAD);
  pMathHIn.r1_c4 = -0.2f;
  pMathHIn.r2_c4 = -0.3f;
  pMathHIn.r3_c4 = -0.1f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.19912225839123f, -0.30000000000000f, -0.10174279076061f, 0.0f, 0.01745329251994f, 0.0f), 1.0e-5f);

  // Y21
  pMathHIn  = AL::Math::TransformFromRotY(-1.0f*TO_RAD);
  pMathHIn.r1_c4 = -0.2f;
  pMathHIn.r2_c4 = -0.3f;
  pMathHIn.r3_c4 = -0.1f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.20086758764323f, -0.30000000000000f, -0.09825213225662f, 0.0f, -0.01745329251994f, 0.0f), 1.0e-5f);

  // Z01
  pMathHIn  = AL::Math::TransformFromRotZ(10.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1745329f), 1.0e-5f);

  // Z02
  pMathHIn  = AL::Math::TransformFromRotZ(150.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.61799387799149f), 1.0e-5f);

  // Z03
  pMathHIn  = AL::Math::TransformFromRotZ(179.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.12413936106983f), 1.0e-5f);

  // Z04
  pMathHIn  = AL::Math::TransformFromRotZ(181.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -3.12413936106983f), 1.0e-5f);

  // Z05
  pMathHIn  = AL::Math::TransformFromRotZ(-179.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -3.12413936106983f), 1.0e-5f);

  // Z06
  pMathHIn  = AL::Math::TransformFromRotZ(-181.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.12413936106983f), 1.0e-5f);

  // Z07
  pMathHIn  = AL::Math::TransformFromRotZ(90.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.57079632679490f), 1.0e-5f);

  // Z08
  pMathHIn  = AL::Math::TransformFromRotZ(10.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.11719931569912f, 0.19076540009837f, 0.30000000000000f, 0.0f, 0.0f, 0.17453292519943f), 1.0e-5f);

  // Z09
  pMathHIn  = AL::Math::TransformFromRotZ(179.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.31377713366518f, -0.15348057293709f, 0.30000000000000f, 0.0f, 0.0f, 3.12413936106983f), 1.0e-5f);

  // Z10
  pMathHIn  = AL::Math::TransformFromRotZ(181.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.31105073854878f, 0.15893336316989f, 0.30000000000000f, 0.0f, 0.0f, -3.12413936106983f), 1.0e-5f);

  // Z11
  pMathHIn  = AL::Math::TransformFromRotZ(179.99f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, +3.14141812066260f), 1.0e-5f); // devrait etre -

  // Z12
  pMathHIn  = AL::Math::TransformFromRotZ(180.01f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, +3.14141812066260f), 1.0e-5f);

  // Z13
  pMathHIn  = AL::Math::TransformFromRotZ(180.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.14159265358979f), 1.0e-5f);

  // Z14
  pMathHIn  = AL::Math::TransformFromRotZ(-179.99f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, +3.14141812066260f), 1.0e-5f); // devrait etre -

  // Z15
  pMathHIn  = AL::Math::TransformFromRotZ(-180.01f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, +3.14141812066260f), 1.0e-5f);

  // Z16
  pMathHIn  = AL::Math::TransformFromRotZ(-180.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, +3.14159265358979f), 1.0e-5f);

  // Z17
  pMathHIn  = AL::Math::TransformFromRotZ(+180.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.31447626090798f, -0.15644564158149f, 0.30000000000000f, 0.0f, 0.0f, 3.14159265358979f), 1.0e-3f);

  // Z18
  pMathHIn  = AL::Math::TransformFromRotZ(+0.1f*TO_RAD);
  pMathHIn.r1_c4 = -0.2f;
  pMathHIn.r2_c4 = -0.3f;
  pMathHIn.r3_c4 = -0.1f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.20026174861823f, -0.29982539092044f, -0.10000000000000f, 0.0f, 0.0f, 0.00174532925199f), 1.0e-5f);

  // Z19
  pMathHIn  = AL::Math::TransformFromRotZ(-0.1f*TO_RAD);
  pMathHIn.r1_c4 = -0.2f;
  pMathHIn.r2_c4 = -0.3f;
  pMathHIn.r3_c4 = -0.1f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.19973814984263f, -0.30017445677084f, -0.10000000000000f, 0.0f, 0.0f, -0.00174532925199f), 1.0e-5f);

  // Z20
  pMathHIn  = AL::Math::TransformFromRotZ(+1.0f*TO_RAD);
  pMathHIn.r1_c4 = -0.2f;
  pMathHIn.r2_c4 = -0.3f;
  pMathHIn.r3_c4 = -0.1f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.20261291689522f, -0.29824705527385f, -0.10000000000000f, 0.0f, 0.0f, 0.01745329251994f), 1.0e-5f);

  // Z21
  pMathHIn  = AL::Math::TransformFromRotZ(-1.0f*TO_RAD);
  pMathHIn.r1_c4 = -0.2f;
  pMathHIn.r2_c4 = -0.3f;
  pMathHIn.r3_c4 = -0.1f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.19737692913924f, -0.30173771377784f, -0.10000000000000f, 0.0f, 0.0f, -0.01745329251994f), 1.0e-5f);

  // 00
  pMathHIn  = AL::Math::TransformFromRotX(0.0f);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 1.0e-5f);

  // 01
  pMathHIn  = AL::Math::TransformFromRotX(0.0f);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.1f, 0.2f, 0.3f, 0.0f, 0.0f, 0.0f), 1.0e-5f);

  // 02
  pMathHIn  = AL::Math::TransformFromRotZ(110.0f*TO_RAD)*AL::Math::TransformFromRotX(-30.0f*TO_RAD)*AL::Math::TransformFromRotY(-150.0f*TO_RAD);
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(0.0f, 0.0f, 0.0f, -2.19530551593940f, 1.78449667326725f, -1.05305343403968f), 1.0e-5f);

  // 03
  pMathHIn  = AL::Math::TransformFromRotZ(110.0f*TO_RAD)*AL::Math::TransformFromRotX(-30.0f*TO_RAD)*AL::Math::TransformFromRotY(-150.0f*TO_RAD);
  pMathHIn.r1_c4 = 0.1f;
  pMathHIn.r2_c4 = 0.2f;
  pMathHIn.r3_c4 = 0.3f;
  pMathVOut = AL::Math::Velocity6D();
  AL::Math::TransformLogarithme(pMathHIn, pMathVOut);
  compareVelocity6D(pMathVOut, AL::Math::Velocity6D(-0.32467607279532f, -0.28979289026856f, 0.35532477264459f, -2.19530551593940f, 1.78449667326725f, -1.05305343403968f), 1.0e-5f);

} // end TransformLogarithme


TEST(ALTransformHelpersTest, VelocityExponential)
{
  // ************ VelocityExponential ************
  AL::Math::Velocity6D pMathVIn  = AL::Math::Velocity6D();
  AL::Math::Transform  pMathHOut = AL::Math::Transform();
  AL::Math::Transform  pMathHSol = AL::Math::Transform();

  AL::Math::VelocityExponential(pMathVIn, pMathHOut);
  compareTransform(pMathHOut, AL::Math::Transform());

  pMathVIn  = AL::Math::Velocity6D(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
  pMathHOut = AL::Math::Transform();
  pMathHSol = AL::Math::Transform();

  pMathHSol.r1_c1 = 0.22629564095021f;
  pMathHSol.r1_c2 = -0.18300791965762f;
  pMathHSol.r1_c3 = 0.95671227870741f;

  pMathHSol.r2_c1 = 0.95671227870741f;
  pMathHSol.r2_c2 = 0.22629564095021f;
  pMathHSol.r2_c3 = -0.18300791965762f;

  pMathHSol.r3_c1 = -0.18300791965762f;
  pMathHSol.r3_c2 = 0.95671227870741f;
  pMathHSol.r3_c3 = 0.22629564095021f;

  pMathHSol.r1_c4 = 1.0f;
  pMathHSol.r2_c4 = 1.0f;
  pMathHSol.r3_c4 = 1.0f;

  AL::Math::VelocityExponential(pMathVIn, pMathHOut);
  compareTransform(pMathHOut, pMathHSol);

  pMathVIn  = AL::Math::Velocity6D(1.0f, 0.4f, -0.2f, -0.5f, 0.6f, -0.7f);
  pMathHOut = AL::Math::Transform();
  pMathHSol = AL::Math::Transform();

  pMathHSol.r1_c1 = 0.61255758028090f;
  pMathHSol.r1_c2 = 0.44179855168103f;
  pMathHSol.r1_c3 = 0.65542905838310f;

  pMathHSol.r2_c1 = -0.71528731854157f;
  pMathHSol.r2_c2 = 0.66269718753866f;
  pMathHSol.r2_c3 = 0.22180281684855f;

  pMathHSol.r3_c1 = -0.33635883037913f;
  pMathHSol.r3_c2 = -0.60468709045331f;
  pMathHSol.r3_c3 = 0.72195308702511f;

  pMathHSol.r1_c4 = 0.90888443200578f;
  pMathHSol.r2_c4 = -0.04541275047598f;
  pMathHSol.r3_c4 = -0.51669980898354f;

  AL::Math::VelocityExponential(pMathVIn, pMathHOut);
  compareTransform(pMathHOut, pMathHSol);

} // end VelocityExponential

TEST(ALTransformHelpersTest, ChangeRepereVelocity6D)
{

}

TEST(ALTransformHelpersTest, ChangeReperePosition6D)
{

}

TEST(ALTransformHelpersTest, ChangeReperePosition3D)
{

}

TEST(ALTransformHelpersTest, ChangeRepereTransposePosition3D)
{

}

TEST(ALTransformHelpersTest, ChangeRepereTransform)
{
}

TEST(ALTransformHelpersTest, ChangeRepereTransposeTransform)
{
}

TEST(ALTransformHelpersTest, ChangeRepereTransposeVelocity6D)
{
}

TEST(ALTransformHelpersTest, ChangeRepereTransposePosition6D)
{
}

TEST(ALTransformHelpersTest, TransformMean)
{
  // ************ TransformMean ************

  // 0
  AL::Math::Transform pMathHIn1 = AL::Math::Transform();
  AL::Math::Transform pMathHIn2 = AL::Math::Transform();
  AL::Math::Transform pMathHOut = AL::Math::Transform();

  AL::Math::TransformMean(pMathHIn1, pMathHIn2, 0.0f, pMathHOut);
  compareTransform(pMathHIn1, pMathHOut);

  // 1
  pMathHIn1 = AL::Math::TransformFromRotX(10.0f*TO_RAD);
  pMathHIn2 = AL::Math::TransformFromRotX(30.0f*TO_RAD);

  AL::Math::TransformMean(pMathHIn1, pMathHIn2, 0.5f, pMathHOut);
  compareTransform(AL::Math::TransformFromRotX(20.0f*TO_RAD), pMathHOut, 5.0e-4f);

  // 2
  pMathHIn1 = AL::Math::TransformFromRotY(10.0f*TO_RAD);
  pMathHIn2 = AL::Math::TransformFromRotY(30.0f*TO_RAD);

  AL::Math::TransformMean(pMathHIn1, pMathHIn2, 0.5f, pMathHOut);
  compareTransform(AL::Math::TransformFromRotY(20.0f*TO_RAD), pMathHOut, 5.0e-4f);

  // 3
  pMathHIn1 = AL::Math::TransformFromRotZ(10.0f*TO_RAD);
  pMathHIn2 = AL::Math::TransformFromRotZ(30.0f*TO_RAD);

  AL::Math::TransformMean(pMathHIn1, pMathHIn2, 0.5f, pMathHOut);
  compareTransform(AL::Math::TransformFromRotZ(20.0f*TO_RAD), pMathHOut, 5.0e-4f);

} // end TransformMean

TEST(ALTransformHelpersTest, TransformFromPosition3D)
{
}

TEST(ALTransformHelpersTest, RotationToTransform)
{
}

TEST(ALTransformHelpersTest, RotationFromTransform)
{
}

TEST(ALTransformHelpersTest, TransformToPosition3D)
{
}

TEST(ALTransformHelpersTest, Position6DFromTransform)
{
}

TEST(ALTransformHelpersTest, TransformFromPose2D)
{
}

TEST(ALTransformHelpersTest, Pose2DFromTransform)
{
}

TEST(ALTransformHelpersTest, TransformFromRotation3D)
{
}

TEST(ALTransformHelpersTest, TransformFromPosition6D)
{
}

TEST(ALTransformHelpersTest, TransformDiffToPosition)
{
  AL::Math::Transform pHCurrent;
  AL::Math::Transform pHTarget;
  AL::Math::Position6D pResult;

  AL::Math::Position6D pExpected;

  // TODO hight priority
  AL::Math::TransformDiffToPosition(pHCurrent, pHTarget, pResult);

  comparePosition6D(pResult, pExpected);
}

TEST(ALTransformHelpersTest, Position3DFromTransformInPlace)
{
}

TEST(ALTransformHelpersTest, Position3DFromTransform)
{
}

TEST(ALTransformHelpersTest, RotationPosition3DToTransform)
{
}

TEST(ALTransformHelpersTest, Rotation3DFromTransform)
{
}

TEST(ALTransformHelpersTest, Rotation2DFromTransformZ)
{
}

TEST(ALTransformHelpersTest, FilterTransform)
{
}

TEST(ALTransformHelpersTest, AxisMaskToTransformOn)
{
}

TEST(ALTransformHelpersTest, computeMixTransformWithAxisMask)
{
}

TEST(ALTransformHelpersTest, RotVecToTransform)
{
}

TEST(ALTransformHelpersTest, AxisRotationProjection)
{
}


TEST(ALTransformHelpersTest, transformAxisRotationProjectionInPlace)
{
  // ************ AxisRotationProjectionInPlace ************

  // 01
  //pMathRIn  = AL::Math::Rotation();
  //pMathPIn  = AL::Math::Position3D();

  //ASSERT_THROW(AxisRotationProjectionInPlace(pMathRIn, pMathPIn), AL::ALError);

  // 02
  AL::Math::Transform  pMathHIn  = AL::Math::Transform();
  AL::Math::Transform  pMathHOut = AL::Math::Transform();
  AL::Math::Position3D pMathPIn  = AL::Math::Position3D(1.0f, 0.0f, 0.0f);

  AL::Math::AxisRotationProjectionInPlace(pMathPIn, pMathHIn);
  compareTransform(pMathHIn, AL::Math::Transform());

  // 03
  pMathHIn  = AL::Math::TransformFromRotX(10.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.0f, 0.0f, 1.0f);

  AL::Math::AxisRotationProjectionInPlace(pMathPIn, pMathHIn);
  compareTransform(pMathHIn, AL::Math::Transform());

  // 04
  pMathHIn  = AL::Math::TransformFromRotY(10.0f*TO_RAD)*AL::Math::TransformFromRotX(10.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.0f, 1.0f, 0.0f);

  AL::Math::AxisRotationProjectionInPlace(pMathPIn, pMathHIn);
  compareTransform(pMathHIn, AL::Math::TransformFromRotY(10.0f*TO_RAD));

  // 05
  pMathHIn  = AL::Math::TransformFromRotZ(110.0f*TO_RAD)*AL::Math::TransformFromRotX(-30.0f*TO_RAD)*AL::Math::TransformFromRotY(-150.0f*TO_RAD);
  pMathHIn.r1_c4 = 10.0f;
  pMathHIn.r2_c4 = -5.0f;
  pMathHIn.r3_c4 = 12.0f;

  pMathPIn  = AL::Math::Position3D(0.5f, 0.5f, 0.0f);

  pMathHOut.r1_c1 = 0.67130774833459f;
  pMathHOut.r1_c2 = 0.32869225166541f;
  pMathHOut.r1_c3 = -0.66430504972634f;
  pMathHOut.r1_c4 = 10.0f;

  pMathHOut.r2_c1 = 0.32869225166541f;
  pMathHOut.r2_c2 = 0.67130774833459f;
  pMathHOut.r2_c3 = 0.66430504972634f;
  pMathHOut.r2_c4 = -5.0f;

  pMathHOut.r3_c1 = 0.66430504972634f;
  pMathHOut.r3_c2 = -0.66430504972634f;
  pMathHOut.r3_c3 = 0.34261549666919f;
  pMathHOut.r3_c4 = 12.0f;

  AL::Math::AxisRotationProjectionInPlace(pMathPIn, pMathHIn);
  compareTransform(pMathHIn, pMathHOut);

  // 06
  pMathHIn  = AL::Math::TransformFromRotZ(110.0f*TO_RAD)*AL::Math::TransformFromRotX(-30.0f*TO_RAD)*AL::Math::TransformFromRotY(-150.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(1.0f, 0.0f, 0.0f);

  pMathHOut = AL::Math::Transform();

  pMathHOut.r1_c1 = 1.0f;
  pMathHOut.r1_c2 = 0.0f;
  pMathHOut.r1_c3 = 0.0f;

  pMathHOut.r2_c1 = 0.0f;
  pMathHOut.r2_c2 = -0.91900358951769f;
  pMathHOut.r2_c3 = -0.39424916290792f;

  pMathHOut.r3_c1 = 0.0f;
  pMathHOut.r3_c2 = 0.39424916290792f;
  pMathHOut.r3_c3 = -0.91900358951769f;

  AL::Math::AxisRotationProjectionInPlace(pMathPIn, pMathHIn);
  compareTransform(pMathHIn, pMathHOut);

  // 07
  pMathHIn  = AL::Math::TransformFromRotZ(110.0f*TO_RAD)*AL::Math::TransformFromRotX(-30.0f*TO_RAD)*AL::Math::TransformFromRotY(-150.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.0f, 1.0f, 0.0f);

  pMathHOut.r1_c1 = -0.14011259929748f;
  pMathHOut.r1_c2 = 0.0f;
  pMathHOut.r1_c3 = 0.99013557633190f;

  pMathHOut.r2_c1 = 0.0f;
  pMathHOut.r2_c2 = 1.0f;
  pMathHOut.r2_c3 = 0.0f;

  pMathHOut.r3_c1 = -0.99013557633190f;
  pMathHOut.r3_c2 = 0.0f;
  pMathHOut.r3_c3 = -0.14011259929748f;

  AL::Math::AxisRotationProjectionInPlace(pMathPIn, pMathHIn);
  compareTransform(pMathHIn, pMathHOut);

  // 08
  pMathHIn  = AL::Math::TransformFromRotZ(110.0f*TO_RAD)*AL::Math::TransformFromRotX(-30.0f*TO_RAD)*AL::Math::TransformFromRotY(-150.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.0f, 0.0f, 1.0f);

  pMathHOut.r1_c1 = +0.34202014332567f;
  pMathHOut.r1_c2 = +0.93969262078591f;
  pMathHOut.r1_c3 = 0.0f;

  pMathHOut.r2_c1 = -0.93969262078591f;
  pMathHOut.r2_c2 = +0.34202014332567f;
  pMathHOut.r2_c3 = 0.0f;

  pMathHOut.r3_c1 = 0.0f;
  pMathHOut.r3_c2 = 0.0f;
  pMathHOut.r3_c3 = 1.0f;

  AL::Math::AxisRotationProjectionInPlace(pMathPIn, pMathHIn);
  compareTransform(pMathHIn, pMathHOut);

} // end transform AxisRotationProjectionInPlace

TEST(ALTransformHelpersTest, rotationAxisRotationProjectionInPlace)
{
  AL::Math::Rotation pMathROut;
  // ************ AxisRotationProjectionInPlace ************

  // 01
  //pMathRIn  = AL::Math::Rotation();
  //pMathPIn  = AL::Math::Position3D();

  //ASSERT_THROW(AxisRotationProjectionInPlace(pMathRIn, pMathPIn), AL::ALError);

  // 02
  AL::Math::Rotation   pMathRIn  = AL::Math::Rotation();
  AL::Math::Position3D pMathPIn  = AL::Math::Position3D(1.0f, 0.0f, 0.0f);

  AL::Math::AxisRotationProjectionInPlace(pMathRIn, pMathPIn);
  compareRotation(pMathRIn, AL::Math::Rotation());

  // 03
  pMathRIn  = AL::Math::RotationFromRotX(10.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.0f, 0.0f, 1.0f);

  AL::Math::AxisRotationProjectionInPlace(pMathRIn, pMathPIn);
  compareRotation(pMathRIn, AL::Math::Rotation());

  // 04
  pMathRIn  = AL::Math::RotationFromRotY(10.0f*TO_RAD)*AL::Math::RotationFromRotX(10.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.0f, 1.0f, 0.0f);

  AL::Math::AxisRotationProjectionInPlace(pMathRIn, pMathPIn);
  compareRotation(pMathRIn, AL::Math::RotationFromRotY(10.0f*TO_RAD));

  // 05
  pMathRIn  = AL::Math::RotationFromRotZ(110.0f*TO_RAD)*AL::Math::RotationFromRotX(-30.0f*TO_RAD)*AL::Math::RotationFromRotY(-150.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.5f, 0.5f, 0.0f);

  pMathROut.r1_c1 = 0.67130774833459f;
  pMathROut.r1_c2 = 0.32869225166541f;
  pMathROut.r1_c3 = -0.66430504972634f;

  pMathROut.r2_c1 = 0.32869225166541f;
  pMathROut.r2_c2 = 0.67130774833459f;
  pMathROut.r2_c3 = 0.66430504972634f;

  pMathROut.r3_c1 = 0.66430504972634f;
  pMathROut.r3_c2 = -0.66430504972634f;
  pMathROut.r3_c3 = 0.34261549666919f;

  AL::Math::AxisRotationProjectionInPlace(pMathRIn, pMathPIn);
  compareRotation(pMathRIn, pMathROut);

  // 06
  pMathRIn  = AL::Math::RotationFromRotZ(110.0f*TO_RAD)*AL::Math::RotationFromRotX(-30.0f*TO_RAD)*AL::Math::RotationFromRotY(-150.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(1.0f, 0.0f, 0.0f);

  pMathROut.r1_c1 = 1.0f;
  pMathROut.r1_c2 = 0.0f;
  pMathROut.r1_c3 = 0.0f;

  pMathROut.r2_c1 = 0.0f;
  pMathROut.r2_c2 = -0.91900358951769f;
  pMathROut.r2_c3 = -0.39424916290792f;

  pMathROut.r3_c1 = 0.0f;
  pMathROut.r3_c2 = 0.39424916290792f;
  pMathROut.r3_c3 = -0.91900358951769f;

  AL::Math::AxisRotationProjectionInPlace(pMathRIn, pMathPIn);
  compareRotation(pMathRIn, pMathROut);

  // 07
  pMathRIn  = AL::Math::RotationFromRotZ(110.0f*TO_RAD)*AL::Math::RotationFromRotX(-30.0f*TO_RAD)*AL::Math::RotationFromRotY(-150.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.0f, 1.0f, 0.0f);

  pMathROut.r1_c1 = -0.14011259929748f;
  pMathROut.r1_c2 = 0.0f;
  pMathROut.r1_c3 = 0.99013557633190f;

  pMathROut.r2_c1 = 0.0f;
  pMathROut.r2_c2 = 1.0f;
  pMathROut.r2_c3 = 0.0f;

  pMathROut.r3_c1 = -0.99013557633190f;
  pMathROut.r3_c2 = 0.0f;
  pMathROut.r3_c3 = -0.14011259929748f;

  AL::Math::AxisRotationProjectionInPlace(pMathRIn, pMathPIn);
  compareRotation(pMathRIn, pMathROut);

  // 08
  pMathRIn  = AL::Math::RotationFromRotZ(110.0f*TO_RAD)*AL::Math::RotationFromRotX(-30.0f*TO_RAD)*AL::Math::RotationFromRotY(-150.0f*TO_RAD);
  pMathPIn  = AL::Math::Position3D(0.0f, 0.0f, 1.0f);

  pMathROut.r1_c1 = +0.34202014332567f;
  pMathROut.r1_c2 = +0.93969262078591f;
  pMathROut.r1_c3 = 0.0f;

  pMathROut.r2_c1 = -0.93969262078591f;
  pMathROut.r2_c2 = +0.34202014332567f;
  pMathROut.r2_c3 = 0.0f;

  pMathROut.r3_c1 = 0.0f;
  pMathROut.r3_c2 = 0.0f;
  pMathROut.r3_c3 = 1.0f;

  AL::Math::AxisRotationProjectionInPlace(pMathRIn, pMathPIn);
  compareRotation(pMathRIn, pMathROut);

} // end rotationAxisRotationProjectionInPlace

TEST(ALTransformHelpersTest, Orthospace)
{
  AL::Math::Position3D pAxis;
  AL::Math::Transform  pH;

  // test 0
  pAxis = AL::Math::Position3D(1.0f, 0.0f, 0.0f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);

  // test 1
  pAxis = AL::Math::Position3D(-0.5f, 0.0f, 0.0f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);

  // test 2
  pAxis = AL::Math::Position3D(0.0f, 1.0f, 0.0f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);

  // test 3
  pAxis = AL::Math::Position3D(0.0f, -0.5f, 0.0f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);

  // test 4
  pAxis = AL::Math::Position3D(0.0f, 0.0f, 1.0f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);

  // test 5
  pAxis = AL::Math::Position3D(0.0f, 0.0f, -0.5f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);

  // test 6
  pAxis = AL::Math::Position3D(1.0f, 1.0f, 1.0f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);

  // test 7
  pAxis = AL::Math::Position3D(-0.5f, -0.5f, -0.5f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);

  // test 8
  pAxis = AL::Math::Position3D(0.01f, -0.5f, -0.5f);
  pH = AL::Math::Orthospace(pAxis);
  EXPECT_NEAR(pH.determinant(), 1.0f, 0.001f);
}


TEST(ALTransformHelpersTest, AxisRotationToTransform)
{
  float angle = 0.0f;
  float Ca = 0.0f;
  float Sa = 0.0f;

  AL::Math::Transform HOut;
  AL::Math::Transform HDes;
  AL::Math::Position3D pAxisRotation;

  // Test rot X
  pAxisRotation = AL::Math::Position3D(1.0f, 0.0f, 0.0f);
  for (unsigned int i=0; i<36; i++)
  {
    angle = i*10.0f*TO_RAD;
    Ca    = cosf(angle);
    Sa    = sinf(angle);

    AxisRotationToTransform(pAxisRotation, Ca, Sa, HOut);

    HDes = AL::Math::TransformFromRotX(angle);
    compareTransform(HOut, HDes, 0.0001f);
  }

  // Test rot Y
  pAxisRotation = AL::Math::Position3D(0.0f, 1.0f, 0.0f);
  for (unsigned int i=0; i<36; i++)
  {
    angle = i*10.0f*TO_RAD;
    Ca    = cosf(angle);
    Sa    = sinf(angle);

    AxisRotationToTransform(pAxisRotation, Ca, Sa, HOut);

    HDes = AL::Math::TransformFromRotY(angle);
    compareTransform(HOut, HDes, 0.0001f);
  }

  // Test rot Z
  pAxisRotation = AL::Math::Position3D(0.0f, 0.0f, 1.0f);
  for (unsigned int i=0; i<36; i++)
  {
    angle = i*10.0f*TO_RAD;
    Ca    = cosf(angle);
    Sa    = sinf(angle);

    AxisRotationToTransform(pAxisRotation, Ca, Sa, HOut);

    HDes = AL::Math::TransformFromRotZ(angle);
    compareTransform(HOut, HDes, 0.0001f);
  }

} // end AxisRotationToTransform

TEST(ALTransformHelpersTest, FindRotation)
{
  AL::Math::Position3D pA;
  AL::Math::Position3D pB;

  // RotZ
  // TODO: i=18 a fixer
  for (unsigned int i=0; i<18; i++)
  {
    float angle = i*10.0f*TO_RAD;
    //std::cout << "i: " << i << std::endl;
    pA = AL::Math::Position3D(0.0f, 0.0f, 1.0f);
    pB = AL::Math::Position3D(0.0f, sinf(angle),cosf(angle));
    validateFindRotation(pA, pB);
  }

  // +X +Y
  pA = AL::Math::Position3D(1.0f, 0.0f, 0.0f);
  pB = AL::Math::Position3D(0.0f, 1.0f, 0.0f);
  validateFindRotation(pA, pB);

  // +X -Y
  pA = AL::Math::Position3D(1.0f, 0.0f, 0.0f);
  pB = AL::Math::Position3D(0.0f, -1.0f, 0.0f);
  validateFindRotation(pA, pB);

  // -X +Y
  pA = AL::Math::Position3D(-1.0f, 0.0f, 0.0f);
  pB = AL::Math::Position3D(0.0f, 1.0f, 0.0f);
  validateFindRotation(pA, pB);

  // -X -Y
  pA = AL::Math::Position3D(-1.0f, 0.0f, 0.0f);
  pB = AL::Math::Position3D(0.0f, -1.0f, 0.0f);
  validateFindRotation(pA, pB);

  // Cas particulier
  // X X
  pA = AL::Math::Position3D(1.0f, 0.0f, 0.0f);
  pB = AL::Math::Position3D(1.0f, 0.0f, 0.0f);
  validateFindRotation(pA, pB);

  // Z Z
  pA = AL::Math::Position3D(0.0f, 0.0f, 1.0f);
  pB = AL::Math::Position3D(0.0f, 0.0f, 1.0f);
  validateFindRotation(pA, pB);

  // TODO: a fixer
  // Y Y
//  pA = AL::Math::Position3D(0.0f, 1.0f, 0.0f);
//  pB = AL::Math::Position3D(0.0f, 1.0f, 0.0f);
//  validateFindRotation(pA, pB);
}

TEST(ALControlExplosionTest, test0)
{
  // Inititalisation
  float Kp = 30.0f;
  float dt = 0.02f;

  AL::Math::Transform  fHTrunkWorld = AL::Math::Transform(0.1f, 0.1f, 0.2f);
  AL::Math::Transform  fHTrunkWorldDes;
  AL::Math::Position6D fDeltaTrunkWorldPosition;
  AL::Math::Velocity6D fVTrunkWorldDes;
  AL::Math::Velocity6D fVTrunkWorldConsigne;
  AL::Math::Velocity6D fVTrunkTorsoConsigne;

  // Main purpose: for an updated fHTrunkWorldDes, compute a control in order to
  // fHTrunkWorld = fHTrunkWorldDes

  for (unsigned int i=0; i<200; i++)
  {
    // Update fHTrunkWorldDes
    fHTrunkWorldDes = AL::Math::TransformFromRotZ(2.0f*i*TO_RAD)*AL::Math::TransformFromRotX(-0.2f*i*TO_RAD)*AL::Math::TransformFromRotY(i*TO_RAD);
    fHTrunkWorldDes.r1_c4 = 0.1f+i*0.1f;
    fHTrunkWorldDes.r2_c4 = 0.1f-i*0.05f;
    fHTrunkWorldDes.r3_c4 = 0.2f+i*0.2f;

    for (unsigned j=0; j<1; j++)
    {
      AL::Math::TransformDiffToPosition(
          fHTrunkWorld,
          fHTrunkWorldDes,
          fDeltaTrunkWorldPosition);

      // Compute BODY VELOCITY DES
      fVTrunkWorldConsigne = fVTrunkWorldDes + Kp * fDeltaTrunkWorldPosition;

      AL::Math::ChangeRepereTransposeVelocity6D(
          fHTrunkWorld,
          fVTrunkWorldConsigne,
          fVTrunkTorsoConsigne);

      AL::Math::Transform fDelta_H_root = AL::Math::VelocityExponential(dt*fVTrunkTorsoConsigne);
      fHTrunkWorld = fHTrunkWorld * fDelta_H_root;
    }
  }

  // On ne met plus a jour fHTrunkWorldDes
  // fHTrunkWorld doit converger vers fHTrunkWorldDes
  for (unsigned j=0; j<100; j++)
  {
    AL::Math::TransformDiffToPosition(
        fHTrunkWorld,
        fHTrunkWorldDes,
        fDeltaTrunkWorldPosition);

    // Compute BODY VELOCITY DES
    fVTrunkWorldConsigne = fVTrunkWorldDes + Kp * fDeltaTrunkWorldPosition;

    AL::Math::ChangeRepereTransposeVelocity6D(
        fHTrunkWorld,
        fVTrunkWorldConsigne,
        fVTrunkTorsoConsigne);

    AL::Math::Transform fDelta_H_root = AL::Math::VelocityExponential(dt*fVTrunkTorsoConsigne);
    fHTrunkWorld = fHTrunkWorld * fDelta_H_root;
  }

}

