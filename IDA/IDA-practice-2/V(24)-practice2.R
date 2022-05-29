library("lmtest")
library("GGally")

data = na.omit(attitude)  # insertion base data

help(attitude)

    # Объясняемая переменная: rating 
    # Регрессоры: raises, critical, advancel
    
    # Для начала проверим зависимость между регрессорами, если некоторые будут 
    # зависить друг от другу, то одного из них нужно будет исключить из рассмотрения.
    
    # Способ 1.
    # Построим линейные модели межуду регрессорами.

model\_auxiliary\_1 = lm(raises ~ critical, data)
summary(model\_auxiliary\_1)

# output
# Coefficients:
#             Estimate Std. Error t value Pr(>|t|)  
# (Intercept)  35.0246    13.8680   2.526   0.0175 *
# critical      0.3960     0.1839   2.153   0.0401 *
#   ---


# Residual standard error: 9.801 on 28 degrees of freedom
# Multiple R-squared:  0.142,	Adjusted R-squared:  0.1114 
# F-statistic: 4.636 on 1 and 28 DF,  p-value: 0.04008
# 
    # Вывод: R^2 оказался очень низким, что говорит нам о том, что построенная 
    # модель очень плохая, кроме того p-value довольно высок, исходя из выше
    # сказанного, можно заключить, что регрессоры raises и critical
    # линейно независимы.


    # Построим оставшиеся всевозможные модели и сделаем вывод.
model\_auxiliary\_2 = lm(raises ~ advance, attitude)
summary(model\_auxiliary\_2)

# output
# Coefficients:
#             Estimate Std. Error t value  Pr(>|t|)    
# (Intercept)  39.7216     6.8967   5.759  3.5e-06 ***
# advance       0.5802     0.1564   3.711  0.000907 ***
#   ---

# 
# Residual standard error: 8.663 on 28 degrees of freedom
# Multiple R-squared:  0.3297,	Adjusted R-squared:  0.3058 
# F-statistic: 13.77 on 1 and 28 DF,  p-value: 0.0009068


model\_auxiliary\_3 = lm(critical ~ advance, data)
summary(model\_auxiliary\_3)

# output
# Coefficients:
#             Estimate Std. Error t value    Pr(>|t|)    
# (Intercept)  63.0674     7.6882   8.203    6.28e-09 ***
# advance       0.2725     0.1743   1.563    0.129    
# ---

# 
# Residual standard error: 9.657 on 28 degrees of freedom
# Multiple R-squared:  0.08028,	Adjusted R-squared:  0.04744 
# F-statistic: 2.444 on 1 and 28 DF,  p-value: 0.1292


    # Вывод:
    # Как итог получаем, что регрессоры raises и advance зависят друг от друга, 
    # поэтому одного из них нужно исключить из будущей модели. В дальнейшем мы 
    # проверим, какой из них полезнее для модели.










    # Построим линейную модель, которая описывает переменную rating через регрессоры
    # raises, critical, advance. При этом помним, что одну из переменных raises и
    # advance желательно исключить из модели, выясним какую.

model\_all = lm(rating ~ raises + critical + advance, data)
summary(model\_all)
# vif(model\_co)
# output
# Coefficients:
#             Estimate    Std. Error  t value   Pr(>|t|)    
# (Intercept) 25.50063    15.60204    1.634     0.114218    
# raises       0.89612    0.22555     3.973     0.000501 ***
# critical    -0.06882    0.20233     -0.340    0.736483    
# advance     -0.31773    0.22014     -1.443    0.160870    
# ---

# 
# Residual standard error: 9.947 on 26 degrees of freedom
# Multiple R-squared:  0.4013,	Adjusted R-squared:  0.3322 
# F-statistic: 5.809 on 3 and 26 DF,  p-value: 0.003537


no\_critical\_model = lm(rating ~ raises + advance, data)
summary(no\_critical\_model)
# output
# Coefficients:
#             Estimate Std. Error t value   Pr(>|t|)    
# (Intercept)  21.9917    11.5114   1.910   0.066753 .  
# raises        0.8752     0.2134   4.101   0.000339 ***
# advance      -0.3243     0.2157  -1.504   0.144200    
# ---

# 
# Residual standard error: 9.783 on 27 degrees of freedom
# Multiple R-squared:  0.3986,	Adjusted R-squared:  0.3541 
# F-statistic: 8.949 on 2 and 27 DF,  p-value: 0.001043


no\_raises\_model = lm(rating ~ critical + advance, data)
summary(no\_raises\_model)
# output
# Coefficients:
#             Estimate Std. Error t value   Pr(>|t|)  
# (Intercept)  47.2659    18.1737   2.601   0.0149   *
# critical      0.1505     0.2422   0.621   0.5396  
# advance       0.1425     0.2329   0.612   0.5458  
# ---

# 
# Residual standard error: 12.37 on 27 degrees of freedom
# Multiple R-squared:  0.03781,	Adjusted R-squared:  -0.03346 
# F-statistic: 0.5305 on 2 and 27 DF,  p-value: 0.5943

    # Вывод:
    # Из анализа построенных моделей видно, что наилучшая из всех регрессий - 
    # no\_critical\_model, которая имеет Adjusted R-squared:  0.3541  и наименьшее 
    # значение p-value: 0.001043. 
    # Проанализируем модель no\_critical\_model.
    # Один из её регрессоров (raises) хорошо связан с описываемой переменной, в то 
    # врямя как, второй регрессор модели (advance) очень плохо с ней связан, его 
    # значение p-value: 0.144200 очень высоко, что говорит о большом количестве 
    # неточной при попытке описания rating через регрессор advance. В итого получаем
    # Adjusted R-squared:  0.3541 и Multiple R-squared:  0.3986, что говорит нам о 
    # том, что модель плохая, скорее всего нужно добавлять ещё регрессоры вместо 
    # advance.










    # Теперь введем в наилучшие модели из прошлого шага (model\_all, no\_critical\_model)
    # логарифмы регрессоров, где это возможно. Это возсожно для каждого регрессора,
    # т.к. все они имеют числовые значения.

model\_all\_log\_1 = lm(rating ~ I(log(raises)) + critical + advance, data)
summary(model\_all\_log\_1)
# output
# Coefficients:
#                  Estimate Std. Error t value      Pr(>|t|)    
# (Intercept)    -152.81517   51.46419  -2.969      0.006339   ** 
# I(log(raises))   56.83671   14.02714   4.052      0.000408   ***
# critical         -0.09279    0.20231  -0.459      0.650289    
# advance          -0.27560    0.21253  -1.297      0.206108    
# ---

# 
# Residual standard error: 9.873 on 26 degrees of freedom
# Multiple R-squared:  0.4102,	Adjusted R-squared:  0.3422 
# F-statistic: 6.028 on 3 and 26 DF,  p-value: 0.002937

model\_all\_log\_2 = lm(rating ~ raises + I(log(critical)) + advance, data)
summary(model\_all\_log\_2)
# output
# Coefficients:
#                  Estimate Std. Error t value    Pr(>|t|)    
# (Intercept)       31.5748    56.5610   0.558    0.581453    
# raises             0.8864     0.2268   3.909    0.000593   ***
# I(log(critical))  -2.4274    14.0154  -0.173    0.863842    
# advance           -0.3210     0.2205  -1.456    0.157342    
# ---

# 
# Residual standard error: 9.963 on 26 degrees of freedom
# Multiple R-squared:  0.3993,	Adjusted R-squared:   0.33 
# F-statistic: 5.762 on 3 and 26 DF,  p-value: 0.003684

model\_all\_log\_3 = lm(rating ~ raises + I(log(advance)) + critical, data)
summary(model\_all\_log\_3)
# output
# Coefficients:
#                  Estimate Std. Error t value     Pr(>|t|)    
# (Intercept)      63.70537   31.44509   2.026     0.053148  .  
# raises            0.88450    0.22237   3.978     0.000496  ***
# I(log(advance))  -13.95696    9.80667  -1.423     0.166565  
# critical         -0.05525    0.20363  -0.271     0.788265    
# ---

# 
# Residual standard error: 9.957 on 26 degrees of freedom
# Multiple R-squared:  0.4001,	Adjusted R-squared:  0.3309 
# F-statistic:  5.78 on 3 and 26 DF,  p-value: 0.003628



    # После логарифмирования регрессора raises Multiple R-squared:  0.4102,	
    # Adjusted R-squared:  0.3422 изменились не сильно, Multiple R-squared возрос
    # на 1,5 процента и Adjusted R-squared снизился на 1,2 процента, но значение p-value
    # понизилось, поэтому мы 
    # больше не будет трогать эту переменную, оставив её в покое (за исключением 
    # дальнейшего изучения квадрата этой переменной).

model\_all\_log\_4 = lm(rating ~ raises + I(log(advance)) + I(log(critical)), data)
summary(model\_all\_log\_4)
# output
# Coefficients:
#                  Estimate     Std. Error  t value  Pr(>|t|)    
# (Intercept)       67.5385     60.4114     1.118    0.273801    
# raises             0.8757     0.2235      3.918    0.000579  ***
# I(log(advance))   -14.1787    9.8125      -1.445   0.160411    
# I(log(critical))  -1.5251     14.0925     -0.108   0.914653    
# ---

# 
# Residual standard error: 9.969 on 26 degrees of freedom
# Multiple R-squared:  0.3986,	Adjusted R-squared:  0.3293 
# F-statistic: 5.745 on 3 and 26 DF,  p-value: 0.003736

    # От логарифмирования регрессоров advance и critical мы не получили пользы, 
    # показатель Multiple R-squared:  0.3986 практически не поменялся, а 
    # показатль Adjusted R-squared:  0.3293 уменьшился, но кроме того значение
    # p-value: 0.003736 стало довольно высоким.

    # Проделаем тоже самое с моделью no\_critical\_model

no\_critical\_model = lm(rating ~ raises + advance, data)

no\_critical\_model\_log\_1 = lm(rating ~ raises + I(log(advance)), data)
summary(no\_critical\_model\_log\_1)
# output
# Coefficients:
#                  Estimate Std. Error t value Pr(>|t|)    
# (Intercept)       61.9131     30.2116   2.049   0.050262  .  
# raises             0.8692     0.2114    4.112   0.000329  ***
# I(log(advance))  -14.3182     9.5478   -1.500   0.145311    
# ---

# 
# Residual standard error: 9.785 on 27 degrees of freedom
# Multiple R-squared:  0.3984,	Adjusted R-squared:  0.3538 
# F-statistic: 8.939 on 2 and 27 DF,  p-value: 0.001049

no\_critical\_model\_log\_2 = lm(rating ~ I(log(raises)) + I(log(advance)), data)
summary(no\_critical\_model\_log\_2)
output
Coefficients:
                Estimate Std. Error t value   Pr(>|t|)    
(Intercept)     -115.572     46.471  -2.487   0.019361  *  
I(log(raises))    55.004     13.119   4.193   0.000265  ***
I(log(advance))  -12.963      9.264  -1.399   0.173132    
---


Residual standard error: 9.711 on 27 degrees of freedom
Multiple R-squared:  0.4074,	Adjusted R-squared:  0.3635 
F-statistic: 9.281 on 2 and 27 DF,  p-value: 0.0008557

    # Как итог получили наилучшую на данный момент модель no\_critical\_model\_log\_2
#plot(no\_critical\_model\_log\_2)




    # Введем в модель всевозможные произведения произведения пар регрессоров, найдем 
    # из них наилучшую

model\_all\_mult\_1 = lm(rating ~ I(log(raises)) + I(critical * advance), data)
summary(model\_all\_mult\_1)
output
Coefficients:
                        Estimate   Std. Error   t value   Pr(>|t|)    
(Intercept)           -1.603e+02   5.330e+01    -3.008    0.005633   ** 
I(log(raises))         5.667e+01   1.382e+01    4.100     0.000339   ***
I(critical * advance) -3.259e-03   2.342e-03    -1.391    0.175475    
---


Residual standard error: 9.715 on 27 degrees of freedom
Multiple R-squared:  0.4069,	Adjusted R-squared:  0.363 
F-statistic: 9.264 on 2 and 27 DF,  p-value: 0.0008645

model\_all\_mult\_2 = lm(rating ~ I(log(raises)) + I(critical^2) + advance, data)
summary(model\_all\_mult\_2)
# output
# Coefficients:
#                  Estimate    Std. Error   t value   Pr(>|t|)    
# (Intercept)    -1.571e+02    5.199e+01    -3.022    0.005579   ** 
# I(log(raises))  5.738e+01    1.391e+01    4.125     0.000337   ***
# I(critical^2)  -8.898e-04    1.417e-03    -0.628    0.535463    
# advance        -2.725e-01    2.118e-01    -1.287    0.209550    
# ---

# 
# Residual standard error: 9.838 on 26 degrees of freedom
# Multiple R-squared:  0.4143,	Adjusted R-squared:  0.3468 
# F-statistic: 6.131 on 3 and 26 DF,  p-value: 0.002693

model\_all\_mult\_3 = lm(rating ~ I(log(raises)) + I(critical^2) + I(advance^2), data)
summary(model\_all\_mult\_3)
# output
# Coefficients:
#                  Estimate   Std. Error   t value    Pr(>|t|)    
# (Intercept)    -1.633e+02    5.403e+01    -3.023    0.005569   ** 
# I(log(raises))  5.751e+01    1.396e+01     4.120    0.000342   ***
# I(critical^2)  -9.771e-04    1.412e-03    -0.692    0.495141    
# I(advance^2)   -2.819e-03    2.191e-03    -1.286    0.209689    
# ---

# 
# Residual standard error: 9.838 on 26 degrees of freedom
# Multiple R-squared:  0.4143,	Adjusted R-squared:  0.3467 
# F-statistic: 6.131 on 3 and 26 DF,  p-value: 0.002694

model\_all\_mult\_4 = lm(rating ~ I(log(raises)) + critical + I(advance^2), data)
summary(model\_all\_mult\_4)
# output
# Coefficients:
#                  Estimate    Std. Error   t value    Pr(>|t|)    
# (Intercept)    -1.585e+02    5.348e+01    -2.964    0.006426   ** 
# I(log(raises))  5.690e+01    1.408e+01     4.041    0.000421   ***
# critical       -1.049e-01    2.018e-01    -0.520    0.607609    
# I(advance^2)   -2.831e-03    2.200e-03    -1.287    0.209569    
# ---

# 
# Residual standard error: 9.877 on 26 degrees of freedom
# Multiple R-squared:  0.4097,	Adjusted R-squared:  0.3416 
# F-statistic: 6.014 on 3 and 26 DF,  p-value: 0.002971


no\_critical\_model\_mult\_1 = lm(rating ~ I(raises^2) + advance, data)
summary(no\_critical\_model\_mult\_1)
# output
# Coefficients:
#              Estimate Std. Error t value Pr(>|t|)    
# (Intercept) 51.307766   8.019086   6.398   7.46e-07   ***
# I(raises^2)  0.006657   0.001686   3.949   0.000507   ***
# advance     -0.353557   0.224881  -1.572   0.127551    
# ---

# 
# Residual standard error: 9.923 on 27 degrees of freedom
# Multiple R-squared:  0.3813,	Adjusted R-squared:  0.3355 
# F-statistic: 8.321 on 2 and 27 DF,  p-value: 0.00153


no\_critical\_model\_mult\_2 = lm(rating ~ I(log(raises)) + I(advance^2), data)
summary(no\_critical\_model\_mult\_2)
# output
# Coefficients:
#                   Estimate   Std. Error   t value   Pr(>|t|)    
# (Intercept)    -1.565e+02   5.262e+01     -2.975    0.006110  ** 
# I(log(raises))   5.457e+01   1.317e+01    4.144     0.000302  ***
# I(advance^2)    -2.885e-03   2.168e-03    -1.331    0.194465    
# ---

# 
# Residual standard error: 9.743 on 27 degrees of freedom
# Multiple R-squared:  0.4035,	Adjusted R-squared:  0.3594 
# F-statistic: 9.133 on 2 and 27 DF,  p-value: 0.0009341



    # Получили 2 наилучшие модели:
    # no\_critical\_model\_log\_2: Multiple R-squared:  0.4074,	 Adjusted R-squared:  0.3635,  p-value: 0.0008557
    # 
    # и
    # 
    # model\_all\_mult\_1 = Multiple R-squared:  0.4069,	 Adjusted R-squared:  0.363,  p-value: 0.0008645
    # 
    # однако их нельзя назвать образцовыми, скорее всего это из-за того, что переменную 
    # raiting нельзя описать через регрессоры advance и critical или там очень сложная
    # зависимость. Лучше конечно использовать другие регрессоры.