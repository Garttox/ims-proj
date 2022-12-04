import math

T = 10
p = 101325
hum = 90

c0 = 0.99999683
c1 = -0.90826951 * 10**-2
c2 = 0.78736169 *10**-4
c3 = -0.61117958 * 10**-6
c4 = 0.43884187 * 10**-8
c5 = -0.29883885 * 10**-10
c6 = 0.21874425 * 10**-12
c7 = -0.17892321 * 10**-14
c8 = 0.11112018 * 10**-16
c9 = -0.30994571 * 10**-19

waterPressure = c0 + T*(c1 + T*(c2 + T*(c3 + T*(c4 + T*(c5 + T*(c6 + T*(c7+ T*(c8 + T*c9))))))))
waterPressure = 6.1078/(waterPressure)**8
waterPressure = waterPressure * hum

p_d = p - waterPressure

R_d = 287.05
R_v = 461.495
P_v = waterPressure

ro = p_d/(R_d*(T+273.15)) + P_v/(R_v*(T+273.15))
print(ro)