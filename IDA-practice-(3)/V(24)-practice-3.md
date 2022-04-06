# Сиразетдинов Рустем КМБО-01-21 Вариант 24
## Практическая работа № 3
___
Набор данных: `r20i_os26c.sav` - **wave 20**;

Набор параметров(обязательные): `sj13.2` , `age ` , `sh5` , `s_marst` , `sj72.5c` , `status`  `sj6.2`

Набор параметров(дополнительные): `sj11.1` , `sj23`

Таблица соответствия параметров:

| **Название параметра в наборе** | **Пояснение** | **Практическое название переменной** |
|:---|:---|---:|
|  uj13.2 | Среднемесячная зарплата на предприятии после вычета налогов за 12 месяцев |`salary` |
| age  | Количество полных лет | `age`|
| sh5 | Пол респондента | `sex`|
| s_marst | Семейное положение | `wed1` , `wed2` , `sed3` |
| sj72.5c | Наличие высшего образования |`h_educ`|
| status | Тип населенного пункта | `city_status`|
| sj1.1.2 | Удовлетворенность условиями труда | `satisfy`|
| sj6.2 | Продолжительность рабочей недели в часах  | `dur`|
| sj11.1 | Официальное трудоустройство | `of`|
| sj23 | Является государство владельцем или совладельцем Вашего предприятия, организации? | `gov`|


___

### Начальная обработака данных
___

Создадим переменную `ds` в которую поместим информацию о выбранных столбцах:
```R
ds = select(ds, sj13.2, age, sh5, s_marst, sj72.5c, status, sj6.2, sj1.1.1, sj11.1, sj23)
```
Теперь обработаем данные для дальнейшей работы с ними

1. Семейное положение - `wed1`, `wed2`, `wed3`
    ```R
    ds["wed"] = ds$p_marst
    ds["wed"] = lapply(ds["wed"], as.character)
    ds$wed1 = 0

    ds$wed1[which(ds$wed == '2')] <- 1
    ds$wed1[which(ds$wed == '6')] <- 1
    ds$wed1 = as.numeric(ds$wed1)

    ds["wed2"] = ds$p_marst
    ds$wed2 = 0

    ds$wed2[which(ds$wed == '4')] <- 1
    ds$wed2[which(ds$wed == '5')] <- 1
    ds$wed2 = as.numeric(ds$wed2)

    ds["wed3"] = ds$p_marst
    ds$wed3 = 0

    ds$wed3[which(ds$wed == '1')] <- 1
    # ds$wed3[which(ds$wed == '3')] <- 1
    ds$wed3 = as.numeric(ds$wed3)
    ```

2. Пол респондента - `sex`
    ```R
    ds["sex"] = ds$ph5
    ds["sex"] = lapply(ds["sex"], as.character)

    ds$sex[which(ds$sex == '1')] <- 1
    ds$sex[which(ds$sex == '2')] <- 0
    ds$sex = as.numeric(ds$sex)
    ```

3. Тип населенного пункта - `city_stasus`
    ```R
    ds["status1"] = ds$status
    ds["status1"] = lapply(ds["status1"], as.character)
    ds["city_status"] = 0
    ds$city_status[which(ds$status1 == '1')] <- 1
    ds$city_status[which(ds$status1 == '2')] <- 1
    ds$city_status = as.numeric(ds$city_status)
    ```

 4. Наличие высшего образования - `h_educ`
    ```R
    ds["higher_educ"] = ds$p_diplom
    ds["higher_educ"] = lapply(ds["higher_educ"], as.character)
    ds["h_educ"] = ds$p_diplom
    ds["h_educ"] = 0
    ds$h_educ[which(ds$higher_educ == '6')] <- 1
    ``` 

5. Среднемесячная зарплата на предприятии после вычета налогов за 12 месяцев - `salary`
    Преобразование в вещественную и нормализация 
    ```R
    sal1 = as.character(ds$pj13.2)
    sal2 = lapply(sal1, as.integer)
    sal = as.numeric(unlist(sal2))

    mean(sal)

    ds["salary"] = (sal - mean(sal)) / sqrt(var(sal))
    ds["salary"]
    ```

6. Продолжительность рабочей недели в часах - `dur`
    Преобразование в вещественную и нормализация
    ```R
    dur1 = as.character(ds$pj6.2)
    dur2 = lapply(dur1, as.integer)
    dur3 = as.numeric(unlist(dur2))

    mean(dur3)

    ds["dur"] = (dur3 - mean(dur3)) / sqrt(var(dur3))
    ds["dur"]
    ```

7. Количество полных лет - `age`
    Преобразование в вещественную и нормализация
    ```R
    age1 = as.character(ds$p_age)
    age2 = lapply(age1, as.integer)
    age3 = as.numeric(unlist(age2))

    mean(age3)

    ds["age"]= (age3 - mean(age3)) / sqrt(var(age3))
    ds["age"]
    ```

8. Удовлетворенность условиями труда - `satisfy`
    ```R
    ds["sat"] = ds$pj1.1.1
    ds["sat"] = lapply(ds["sat"], as.character)
    ds["satisfy"] = 0
    ds$satisfy[which(ds$sat == '1')] <- 1
    ds$satisfy[which(ds$sat == '2')] <- 1
    ds$satisfy[which(ds$sat == '3')] <- 1
    ds$satisfy = as.numeric(ds$satisfy)
    ```
9.  Официальное трудоустройство - `of`
    ```R
    ds["of_w"] = ds$pj1.1.1
    ds["of_w"] = lapply(ds["of_w"], as.character)
    ds["of"] = 0
    ds$of[which(ds$of_w == '1')] <- 1
    ds$of = as.numeric(ds$of)
    ```
10. Является государство владельцем или совладельцем Вашего предприятия, организации?
    ```R
    ds["gov_1"] = ds$pj11.1
    ds["gov_1"] = lapply(ds["gov_1"], as.character)
    ds["gov"] = 0
    ds$gov[which(ds$gov_1 == '1')] <- 1
    ds$gov = as.numeric(ds$gov)
    ```

---
### Point 1
---

Построим линейную регрессию переменной `salary` от всех выделенных ранее регрессоров и оценим коэффициент вздутия `VIF`

```R
ds_2 = select(ds, salary, age, sex, h_educ, city_status, dur, wed1, wed2, wed3, satisfy, of, gov)

# модель_1 - `model_def`
model_def = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                 dur + wed1 + wed2 + wed3 + satisfy + of + gov)
summary(model_def)
vif(model_def)
```

Давайте посмотрим на результат:
```R
Call: lm(formula = salary ~ age + sex + h_educ + city_status + dur + 
    wed1 + wed2 + wed3 + satisfy + of + gov, data = ds_2)

Residuals:
    Min      1Q  Median      3Q     Max 
-2.1236 -0.5180 -0.1703  0.2943 10.4633 

Coefficients:
            Estimate Std. Error t value Pr(>|t|)    
(Intercept) -1.03259    0.06699 -15.413  < 2e-16 ***
age         -0.06357    0.01320  -4.814 1.51e-06 ***
sex          0.49299    0.02534  19.456  < 2e-16 ***
h_educ       0.51861    0.02628  19.734  < 2e-16 ***
city_status  0.33425    0.02652  12.603  < 2e-16 ***
dur          0.13087    0.01226  10.672  < 2e-16 ***
wed1         0.03696    0.03733   0.990 0.322194    
wed2        -0.01408    0.04761  -0.296 0.767452    
wed3        -0.11033    0.04697  -2.349 0.018847 *  
satisfy      0.23748    0.03463   6.858 7.72e-12 ***
of           0.29224    0.03452   8.465  < 2e-16 ***
gov          0.17184    0.04992   3.442 0.000581 ***
---
Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

Residual standard error: 0.8972 on 5772 degrees of freedom
Multiple R-squared:  0.1966,	Adjusted R-squared:  0.195 
F-statistic: 128.4 on 11 and 5772 DF,  p-value: < 2.2e-16

> vif(model_def)
        age         sex      h_educ city_status         dur        wed1 
   1.252570    1.138695    1.071094    1.026265    1.080268    2.425066 
       wed2        wed3     satisfy          of         gov 
   2.025865    1.920659    1.035515    1.037693    1.031553 
```

Как можно видеть по данным регрессоры `wed1` и `wed2` плохо описывают поведение переменной `salary`. Возможно одна зависит от другой или они вовсе не нужны в моделе. 

---
### Point 2
---

Построим некоторые другие модели и выберем из них наилучшую:

1. модель_2 - `model_2`
    ```R
    model_2 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                    dur + wed2 + wed3 + satisfy + of + gov)
    ```
    
    Вывод:
    ```R

    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -1.00537    0.06109 -16.456  < 2e-16 ***
    age         -0.06206    0.01312  -4.732 2.28e-06 ***
    sex          0.49382    0.02533  19.499  < 2e-16 ***
    h_educ       0.52052    0.02621  19.860  < 2e-16 ***
    city_status  0.33311    0.02650  12.572  < 2e-16 ***
    dur          0.13046    0.01226  10.645  < 2e-16 ***
    wed2        -0.04508    0.03587  -1.257 0.208843    
    wed3        -0.13923    0.03680  -3.783 0.000156 ***
    satisfy      0.23734    0.03463   6.854 7.94e-12 ***
    of           0.29334    0.03450   8.501  < 2e-16 ***
    gov          0.17498    0.04982   3.512 0.000447 ***
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8972 on 5773 degrees of freedom
    Multiple R-squared:  0.1964,	Adjusted R-squared:  0.195 
    F-statistic: 141.1 on 10 and 5773 DF,  p-value: < 2.2e-16

    > vif(model_2)
        age         sex      h_educ city_status         dur        wed2 
   1.235805    1.137460    1.065350    1.024354    1.079075    1.149644 
       wed3     satisfy          of         gov 
   1.179151    1.035497    1.036630    1.027390 
    ```

2.  модель_3 - `model_3`
    ```R
    model_3 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
               dur + wed3 + satisfy + of + gov)
    ```
    
    Вывод:
    ```R 
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -1.01803    0.06026 -16.894  < 2e-16 ***
    age         -0.06542    0.01284  -5.094 3.61e-07 ***
    sex          0.50181    0.02452  20.469  < 2e-16 ***
    h_educ       0.52143    0.02620  19.902  < 2e-16 ***
    city_status  0.33185    0.02648  12.533  < 2e-16 ***
    dur          0.12995    0.01225  10.609  < 2e-16 ***
    wed3        -0.13527    0.03667  -3.689 0.000227 ***
    satisfy      0.23784    0.03463   6.869 7.16e-12 ***
    of           0.29268    0.03450   8.483  < 2e-16 ***
    gov          0.17740    0.04978   3.563 0.000369 ***
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8972 on 5774 degrees of freedom
    Multiple R-squared:  0.1962,	Adjusted R-squared:  0.195 
    F-statistic: 156.6 on 9 and 5774 DF,  p-value: < 2.2e-16

    > vif(model_3)
             age         sex      h_educ city_status         dur        wed3 
        1.184470    1.065777    1.064537    1.022876    1.077890    1.170538 
         satisfy          of         gov 
        1.035357    1.036389    1.025854 
    ```

3.  модель_4 - `model_4`
    ```R
    model_4 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                dur + wed3 + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -1.01803    0.06026 -16.894  < 2e-16 ***
    age         -0.06542    0.01284  -5.094 3.61e-07 ***
    sex          0.50181    0.02452  20.469  < 2e-16 ***
    h_educ       0.52143    0.02620  19.902  < 2e-16 ***
    city_status  0.33185    0.02648  12.533  < 2e-16 ***
    dur          0.12995    0.01225  10.609  < 2e-16 ***
    wed3        -0.13527    0.03667  -3.689 0.000227 ***
    satisfy      0.23784    0.03463   6.869 7.16e-12 ***
    of           0.29268    0.03450   8.483  < 2e-16 ***
    gov          0.17740    0.04978   3.563 0.000369 ***
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8972 on 5774 degrees of freedom
    Multiple R-squared:  0.1962,	Adjusted R-squared:  0.195 
    F-statistic: 156.6 on 9 and 5774 DF,  p-value: < 2.2e-16

    > vif(model_4)
             age         sex      h_educ city_status         dur        wed3 
        1.184470    1.065777    1.064537    1.022876    1.077890    1.170538 
         satisfy          of         gov 
        1.035357    1.036389    1.025854 
    ```

4.  модель_5 - `model_5`
    ```R
    model_5 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
            log(dur) + wed3 + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -1.38986    0.16679  -8.333 3.22e-16 ***
    log(age)    -0.19561    0.04326  -4.522 7.01e-06 ***
    sex          0.56428    0.07208   7.829 1.49e-14 ***
    h_educ       0.63077    0.08806   7.163 1.73e-12 ***
    city_status  0.46811    0.07522   6.223 7.68e-10 ***
    log(dur)     0.14344    0.03867   3.710 0.000221 ***
    wed3        -0.06911    0.21784  -0.317 0.751120    
    satisfy      0.28575    0.09670   2.955 0.003214 ** 
    of           0.38896    0.10493   3.707 0.000224 ***
    gov          0.40415    0.12620   3.202 0.001414 ** 
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1.013 on 836 degrees of freedom
    Multiple R-squared:  0.2212,	Adjusted R-squared:  0.2128 
    F-statistic: 26.38 on 9 and 836 DF,  p-value: < 2.2e-16

    > vif(model_5)
    log(age)         sex      h_educ city_status    log(dur)        wed3 
    1.009007    1.066086    1.039785    1.055698    1.074416    1.034433 
         satisfy          of         gov 
        1.033583    1.042468    1.034982     
    ```

5.  модель_6 - `model_6`
    ```R
    model_6 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
               log(dur) + wed3 + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -1.38986    0.16679  -8.333 3.22e-16 ***
    log(age)    -0.19561    0.04326  -4.522 7.01e-06 ***
    sex          0.56428    0.07208   7.829 1.49e-14 ***
    h_educ       0.63077    0.08806   7.163 1.73e-12 ***
    city_status  0.46811    0.07522   6.223 7.68e-10 ***
    log(dur)     0.14344    0.03867   3.710 0.000221 ***
    wed3        -0.06911    0.21784  -0.317 0.751120    
    satisfy      0.28575    0.09670   2.955 0.003214 ** 
    of           0.38896    0.10493   3.707 0.000224 ***
    gov          0.40415    0.12620   3.202 0.001414 ** 
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1.013 on 836 degrees of freedom
    Multiple R-squared:  0.2212,	Adjusted R-squared:  0.2128 
    F-statistic: 26.38 on 9 and 836 DF,  p-value: < 2.2e-16

    > vif(model_6)
    log(age)         sex      h_educ city_status    log(dur)        wed3 
    1.009007    1.066086    1.039785    1.055698    1.074416    1.034433 
         satisfy          of         gov 
        1.033583    1.042468    1.034982
    ```

6.  модель_7 - `model_7`
    ```R
    model_7 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               log(dur) + wed3 + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -0.806083   0.099525  -8.099 9.68e-16 ***
    I(age^2)    -0.189591   0.024424  -7.763 1.34e-14 ***
    sex          0.577242   0.045879  12.582  < 2e-16 ***
    h_educ       0.607754   0.054626  11.126  < 2e-16 ***
    city_status  0.395695   0.049110   8.057 1.35e-15 ***
    log(dur)     0.112069   0.024147   4.641 3.70e-06 ***
    wed3        -0.004729   0.065708  -0.072   0.9426    
    satisfy      0.262643   0.061808   4.249 2.25e-05 ***
    of           0.324860   0.066965   4.851 1.33e-06 ***
    gov          0.167293   0.074947   2.232   0.0257 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.9857 on 1935 degrees of freedom
    Multiple R-squared:  0.2169,	Adjusted R-squared:  0.2132 
    F-statistic: 59.54 on 9 and 1935 DF,  p-value: < 2.2e-16

    > vif(model_7)
    I(age^2)         sex      h_educ city_status    log(dur)        wed3 
    1.085653    1.041083    1.049065    1.034701    1.057232    1.080937 
         satisfy          of         gov 
        1.038009    1.046402    1.028206 
    ```

7.  модель_8 - `model_8`
    ```R
    model_8 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               I(dur^2) + wed3 + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -0.885618   0.061460 -14.410  < 2e-16 ***
    I(age^2)    -0.147415   0.011051 -13.339  < 2e-16 ***
    sex          0.564877   0.023921  23.614  < 2e-16 ***
    h_educ       0.499908   0.026007  19.222  < 2e-16 ***
    city_status  0.345314   0.026427  13.066  < 2e-16 ***
    I(dur^2)     0.009851   0.003183   3.095  0.00198 ** 
    wed3         0.012800   0.034397   0.372  0.70982    
    satisfy      0.242118   0.034544   7.009 2.68e-12 ***
    of           0.316647   0.034409   9.202  < 2e-16 ***
    gov          0.120238   0.049649   2.422  0.01548 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8944 on 5774 degrees of freedom
    Multiple R-squared:  0.2012,	Adjusted R-squared:    0.2 
    F-statistic: 161.6 on 9 and 5774 DF,  p-value: < 2.2e-16

    > vif(model_8)
    I(age^2)         sex      h_educ city_status    I(dur^2)        wed3 
    1.037139    1.021009    1.055458    1.025365    1.013583    1.036519 
         satisfy          of         gov 
        1.036814    1.037240    1.026681 
    ```

8.  модель_9 - `model_9`
    ```R
    model_9 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               I(dur^2) + wed3 + I(satisfy^2) + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -0.885618   0.061460 -14.410  < 2e-16 ***
    I(age^2)     -0.147415   0.011051 -13.339  < 2e-16 ***
    sex           0.564877   0.023921  23.614  < 2e-16 ***
    h_educ        0.499908   0.026007  19.222  < 2e-16 ***
    city_status   0.345314   0.026427  13.066  < 2e-16 ***
    I(dur^2)      0.009851   0.003183   3.095  0.00198 ** 
    wed3          0.012800   0.034397   0.372  0.70982    
    I(satisfy^2)  0.242118   0.034544   7.009 2.68e-12 ***
    of            0.316647   0.034409   9.202  < 2e-16 ***
    gov           0.120238   0.049649   2.422  0.01548 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8944 on 5774 degrees of freedom
    Multiple R-squared:  0.2012,	Adjusted R-squared:    0.2 
    F-statistic: 161.6 on 9 and 5774 DF,  p-value: < 2.2e-16

    > vif(model_9)
        I(age^2)          sex       h_educ  city_status     I(dur^2) 
        1.037139     1.021009     1.055458     1.025365     1.013583 
            wed3 I(satisfy^2)           of          gov 
        1.036519     1.036814     1.037240     1.026681 
    ```

9.  модель_10 - `model_10`
    ```R
    model_10 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               log(dur) + wed3 + I(satisfy^2) + of + gov)
    ```
    
    Вывод:
    ```R
    Call:
    lm(formula = salary ~ age + sex + h_educ + city_status + dur + 
        wed2 + wed3 + satisfy + of + gov, data = ds_2)

    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -0.806083   0.099525  -8.099 9.68e-16 ***
    I(age^2)     -0.189591   0.024424  -7.763 1.34e-14 ***
    sex           0.577242   0.045879  12.582  < 2e-16 ***
    h_educ        0.607754   0.054626  11.126  < 2e-16 ***
    city_status   0.395695   0.049110   8.057 1.35e-15 ***
    log(dur)      0.112069   0.024147   4.641 3.70e-06 ***
    wed3         -0.004729   0.065708  -0.072   0.9426    
    I(satisfy^2)  0.262643   0.061808   4.249 2.25e-05 ***
    of            0.324860   0.066965   4.851 1.33e-06 ***
    gov           0.167293   0.074947   2.232   0.0257 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.9857 on 1935 degrees of freedom
    Multiple R-squared:  0.2169,	Adjusted R-squared:  0.2132 
    F-statistic: 59.54 on 9 and 1935 DF,  p-value: < 2.2e-16


    > vif(model_10)
        I(age^2)          sex       h_educ  city_status     log(dur) 
        1.085653     1.041083     1.049065     1.034701     1.057232 
            wed3 I(satisfy^2)           of          gov 
        1.080937     1.038009     1.046402     1.028206 
    ```

10. модель_11 - `model_11`
    ```R
    model_11 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               log(dur) + wed3 + I(satisfy^2) + of + gov)
    ```
    
    Вывод:
    ```R
        Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -0.806083   0.099525  -8.099 9.68e-16 ***
    I(age^2)     -0.189591   0.024424  -7.763 1.34e-14 ***
    sex           0.577242   0.045879  12.582  < 2e-16 ***
    h_educ        0.607754   0.054626  11.126  < 2e-16 ***
    city_status   0.395695   0.049110   8.057 1.35e-15 ***
    log(dur)      0.112069   0.024147   4.641 3.70e-06 ***
    wed3         -0.004729   0.065708  -0.072   0.9426    
    I(satisfy^2)  0.262643   0.061808   4.249 2.25e-05 ***
    of            0.324860   0.066965   4.851 1.33e-06 ***
    gov           0.167293   0.074947   2.232   0.0257 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.9857 on 1935 degrees of freedom
    Multiple R-squared:  0.2169,	Adjusted R-squared:  0.2132 
    F-statistic: 59.54 on 9 and 1935 DF,  p-value: < 2.2e-16

    > vif(model_11)
        I(age^2)          sex       h_educ  city_status     log(dur) 
        1.085653     1.041083     1.049065     1.034701     1.057232 
            wed3 I(satisfy^2)           of          gov 
        1.080937     1.038009     1.046402     1.028206 
    ```

11. модель_12 - `model_12`
    ```R
    model_12 = lm(data = ds_2, salary ~ I(age^0.1) + sex + h_educ + city_status +
                dur + I(satisfy^2) + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept)   0.73571    0.22483   3.272 0.001080 ** 
    I(age^0.1)   -1.92185    0.21873  -8.786  < 2e-16 ***
    sex           0.42329    0.03345  12.654  < 2e-16 ***
    h_educ        0.51306    0.03670  13.978  < 2e-16 ***
    city_status   0.36291    0.03513  10.331  < 2e-16 ***
    dur           0.12613    0.01635   7.712 1.72e-14 ***
    I(satisfy^2)  0.21390    0.04585   4.666 3.23e-06 ***
    of            0.27076    0.04856   5.575 2.71e-08 ***
    gov           0.26573    0.07316   3.632 0.000286 ***
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8369 on 2711 degrees of freedom
    Multiple R-squared:  0.2109,	Adjusted R-squared:  0.2085 
    F-statistic: 90.54 on 8 and 2711 DF,  p-value: < 2.2e-16
        
    > vif(model_12)
        I(age^0.1)          sex       h_educ  city_status          dur 
          1.024460     1.059381     1.044762     1.020193     1.080962 
      I(satisfy^2)           of          gov 
          1.034417     1.039314     1.014800 

    ```

12. модель_13 - `model_13`
    ```R
    model_13 = lm(data = ds_2, salary ~ I(age^0.5) + sex + h_educ + city_status +
                dur + I(satisfy^2) + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -0.66145    0.09655  -6.851 9.04e-12 ***
    I(age^0.5)   -0.51647    0.05321  -9.706  < 2e-16 ***
    sex           0.42565    0.03335  12.762  < 2e-16 ***
    h_educ        0.51776    0.03660  14.147  < 2e-16 ***
    city_status   0.36490    0.03503  10.418  < 2e-16 ***
    dur           0.12248    0.01633   7.501 8.51e-14 ***
    I(satisfy^2)  0.21585    0.04571   4.722 2.45e-06 ***
    of            0.27557    0.04843   5.690 1.40e-08 ***
    gov           0.25996    0.07293   3.564 0.000371 ***
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8344 on 2711 degrees of freedom
    Multiple R-squared:  0.2156,	Adjusted R-squared:  0.2133 
    F-statistic: 93.16 on 8 and 2711 DF,  p-value: < 2.2e-16

    > vif(model_13)
      I(age^0.5)          sex       h_educ  city_status          dur 
        1.029060     1.059685     1.045035     1.020380     1.084150 
    I(satisfy^2)           of          gov 
        1.034514     1.039754     1.014577 
    ```

13. модель_14 - `model_14`
    ```R
    model_14 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                log(dur) + I(satisfy^2) + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -1.39116    0.16665  -8.348 2.87e-16 ***
    log(age)     -0.19572    0.04323  -4.527 6.85e-06 ***
    sex           0.56719    0.07145   7.938 6.58e-15 ***
    h_educ        0.62861    0.08775   7.164 1.72e-12 ***
    city_status   0.46660    0.07503   6.219 7.88e-10 ***
    log(dur)      0.14340    0.03864   3.711 0.000220 ***
    I(satisfy^2)  0.28644    0.09662   2.965 0.003117 ** 
    of            0.39069    0.10474   3.730 0.000204 ***
    gov           0.40243    0.12602   3.193 0.001458 ** 
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1.013 on 837 degrees of freedom
    Multiple R-squared:  0.2211,	Adjusted R-squared:  0.2136 
    F-statistic:  29.7 on 8 and 837 DF,  p-value: < 2.2e-16

    > vif(model_14)
        log(age)          sex       h_educ  city_status     log(dur) 
        1.008946     1.048829     1.033561     1.051474     1.074406 
    I(satisfy^2)           of          gov 
        1.033058     1.039658     1.033064
    ```

14. модель_15 - `model_15`
    ```R
    model_15 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                log(dur) + I(satisfy^0.5) + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
               Estimate Std. Error t value Pr(>|t|)    
    (Intercept)    -1.39116    0.16665  -8.348 2.87e-16 ***
    log(age)       -0.19572    0.04323  -4.527 6.85e-06 ***
    sex             0.56719    0.07145   7.938 6.58e-15 ***
    h_educ          0.62861    0.08775   7.164 1.72e-12 ***
    city_status     0.46660    0.07503   6.219 7.88e-10 ***
    log(dur)        0.14340    0.03864   3.711 0.000220 ***
    I(satisfy^0.5)  0.28644    0.09662   2.965 0.003117 ** 
    of              0.39069    0.10474   3.730 0.000204 ***
    gov             0.40243    0.12602   3.193 0.001458 ** 
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1.013 on 837 degrees of freedom
    Multiple R-squared:  0.2211,	Adjusted R-squared:  0.2136 
    F-statistic:  29.7 on 8 and 837 DF,  p-value: < 2.2e-16


    > vif(model_15)
        log(age)            sex         h_educ    city_status 
        1.008946       1.048829       1.033561       1.051474 
        log(dur) I(satisfy^0.5)             of            gov 
        1.074406       1.033058       1.039658       1.033064 
    ```

15. модель_16 - `model_16`
    ```R
    model_16 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                log(dur)  + I(satisfy^1.5) + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
               Estimate Std. Error t value Pr(>|t|)    
    (Intercept)    -1.39116    0.16665  -8.348 2.87e-16 ***
    log(age)       -0.19572    0.04323  -4.527 6.85e-06 ***
    sex             0.56719    0.07145   7.938 6.58e-15 ***
    h_educ          0.62861    0.08775   7.164 1.72e-12 ***
    city_status     0.46660    0.07503   6.219 7.88e-10 ***
    log(dur)        0.14340    0.03864   3.711 0.000220 ***
    I(satisfy^0.5)  0.28644    0.09662   2.965 0.003117 ** 
    of              0.39069    0.10474   3.730 0.000204 ***
    gov             0.40243    0.12602   3.193 0.001458 ** 
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1.013 on 837 degrees of freedom
    Multiple R-squared:  0.2211,	Adjusted R-squared:  0.2136 
    F-statistic:  29.7 on 8 and 837 DF,  p-value: < 2.2e-16

    > vif(model_16)
        log(age)            sex         h_educ    city_status 
        1.008946       1.048829       1.033561       1.051474 
        log(dur) I(satisfy^0.5)             of            gov 
        1.074406       1.033058       1.039658       1.033064
    ```

16. модель_17 - `model_17`
    ```R
    model_17 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                    log(dur) + I(satisfy^2) + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -0.98408    0.09878  -9.962  < 2e-16 ***
    age          -0.05213    0.02369  -2.200   0.0279 *  
    sex           0.56649    0.04662  12.150  < 2e-16 ***
    h_educ        0.62089    0.05536  11.215  < 2e-16 ***
    city_status   0.38111    0.04988   7.641 3.36e-14 ***
    log(dur)      0.12104    0.02449   4.943 8.35e-07 ***
    I(satisfy^2)  0.25514    0.06274   4.067 4.96e-05 ***
    of            0.29991    0.06786   4.419 1.05e-05 ***
    gov           0.19042    0.07618   2.500   0.0125 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1.001 on 1936 degrees of freedom
    Multiple R-squared:  0.1925,	Adjusted R-squared:  0.1891 
    F-statistic: 57.68 on 8 and 1936 DF,  p-value: < 2.2e-16

    > vif(model_17)
             age          sex       h_educ  city_status     log(dur) 
        1.008961     1.043213     1.045498     1.035510     1.054786 
    I(satisfy^2)           of          gov 
        1.037665     1.042778     1.030724 
    ```

17. модель_18 - `model_18`
    ```R
    model_18 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                I(dur^2) + I(satisfy^2) + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -1.236089   0.088460 -13.973  < 2e-16 ***
    log(age)     -0.192734   0.020448  -9.426  < 2e-16 ***
    sex           0.473786   0.033086  14.320  < 2e-16 ***
    h_educ        0.489537   0.036965  13.243  < 2e-16 ***
    city_status   0.354453   0.035506   9.983  < 2e-16 ***
    I(dur^2)      0.009629   0.003676   2.620 0.008855 ** 
    I(satisfy^2)  0.227148   0.046341   4.902 1.01e-06 ***
    of            0.276562   0.049080   5.635 1.93e-08 ***
    gov           0.270378   0.074116   3.648 0.000269 ***
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8459 on 2711 degrees of freedom
    Multiple R-squared:  0.1939,	Adjusted R-squared:  0.1915 
    F-statistic:  81.5 on 8 and 2711 DF,  p-value: < 2.2e-16

    > vif(model_18)
        log(age)          sex       h_educ  city_status     I(dur^2) 
        1.006512     1.014595     1.037379     1.020238     1.014173 
    I(satisfy^2)           of          gov 
        1.034546     1.039193     1.019520 
    ```

18. модель_19 - `model_19`
    ```R
    model_19 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                I(dur^0.1) + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -2.29310    0.26668  -8.599  < 2e-16 ***
    age         -0.05173    0.02368  -2.185   0.0290 *  
    sex          0.56489    0.04660  12.122  < 2e-16 ***
    h_educ       0.62154    0.05533  11.232  < 2e-16 ***
    city_status  0.38165    0.04985   7.656 3.00e-14 ***
    I(dur^0.1)   1.30480    0.25384   5.140 3.02e-07 ***
    satisfy      0.25617    0.06271   4.085 4.59e-05 ***
    of           0.29954    0.06783   4.416 1.06e-05 ***
    gov          0.19191    0.07614   2.520   0.0118 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1 on 1936 degrees of freedom
    Multiple R-squared:  0.1933,	Adjusted R-squared:   0.19 
    F-statistic: 57.98 on 8 and 1936 DF,  p-value: < 2.2e-16

    > vif(model_19)
             age         sex      h_educ city_status  I(dur^0.1)     satisfy 
        1.009044    1.043215    1.045513    1.035431    1.055099    1.037786 
              of         gov 
        1.042789    1.030825 
    ```

19. модель_20 - `model_20`
    ```R
    model_20 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
                I(dur^0.5) + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -1.10310    0.11188  -9.860  < 2e-16 ***
    I(age^2)    -0.18832    0.02350  -8.013 1.91e-15 ***
    sex          0.57424    0.04576  12.550  < 2e-16 ***
    h_educ       0.60937    0.05446  11.190  < 2e-16 ***
    city_status  0.39628    0.04901   8.086 1.08e-15 ***
    I(dur^0.5)   0.26856    0.05170   5.195 2.26e-07 ***
    satisfy      0.26638    0.06172   4.316 1.67e-05 ***
    of           0.32401    0.06681   4.849 1.34e-06 ***
    gov          0.16972    0.07480   2.269   0.0234 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.9841 on 1936 degrees of freedom
    Multiple R-squared:  0.219,	Adjusted R-squared:  0.2158 
    F-statistic: 67.87 on 8 and 1936 DF,  p-value: < 2.2e-16

    > vif(model_20)
        I(age^2)         sex      h_educ city_status  I(dur^0.5)     satisfy 
        1.008456    1.038893    1.046044    1.033936    1.055117    1.038453 
              of         gov 
        1.045138    1.027501 
    ```

20. модель_21 - `model_21`
    ```R
    model_21 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
                I(dur^2) + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -0.884254   0.061346 -14.414  < 2e-16 ***
    I(age^2)    -0.146713   0.010888 -13.474  < 2e-16 ***
    sex          0.564977   0.023918  23.622  < 2e-16 ***
    h_educ       0.500315   0.025982  19.256  < 2e-16 ***
    city_status  0.345657   0.026409  13.088  < 2e-16 ***
    I(dur^2)     0.009849   0.003183   3.094  0.00198 ** 
    satisfy      0.242160   0.034541   7.011 2.64e-12 ***
    of           0.316454   0.034403   9.199  < 2e-16 ***
    gov          0.119507   0.049607   2.409  0.01602 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 0.8944 on 5775 degrees of freedom
    Multiple R-squared:  0.2012,	Adjusted R-squared:  0.2001 
    F-statistic: 181.8 on 8 and 5775 DF,  p-value: < 2.2e-16

    > vif(model_21)
    I(age^2)         sex      h_educ city_status    I(dur^2)     satisfy 
    1.006900    1.020881    1.053589    1.024119    1.013581    1.036802 
            of         gov 
    1.037005    1.025070 
    ```

21. модель_22 - `model_22`
    ```R
    model_22 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                log(dur) + satisfy + of + gov)
    ```
    
    Вывод:
    ```R
    Coefficients:
                Estimate Std. Error t value Pr(>|t|)    
    (Intercept) -0.98408    0.09878  -9.962  < 2e-16 ***
    age         -0.05213    0.02369  -2.200   0.0279 *  
    sex          0.56649    0.04662  12.150  < 2e-16 ***
    h_educ       0.62089    0.05536  11.215  < 2e-16 ***
    city_status  0.38111    0.04988   7.641 3.36e-14 ***
    log(dur)     0.12104    0.02449   4.943 8.35e-07 ***
    satisfy      0.25514    0.06274   4.067 4.96e-05 ***
    of           0.29991    0.06786   4.419 1.05e-05 ***
    gov          0.19042    0.07618   2.500   0.0125 *  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1.001 on 1936 degrees of freedom
    Multiple R-squared:  0.1925,	Adjusted R-squared:  0.1891 
    F-statistic: 57.68 on 8 and 1936 DF,  p-value: < 2.2e-16

    > vif(model_22)
                 age         sex      h_educ city_status    log(dur)     satisfy 
            1.008961    1.043213    1.045498    1.035510    1.054786    1.037665 
                  of         gov 
            1.042778    1.030724 
    ```
    
---
### Point 3
---

Из построенных моделей можно выделить следующие с самыми высокими показателями `Multiple R-squared` и `Adjusted R-squared`:

1. модель_5 - `model_5` : `Multiple R-squared = 0.2212`  & `Adjusted R-squared = 0.2128` 

2. модель_6 - `model_6` : `Multiple R-squared = 0.2212`  & `Adjusted R-squared = 0.2128`

3. модель_14 - `model_14` : `Multiple R-squared = 0.2211`  & `Adjusted R-squared = 0.2136`

4. модель_15 - `model_15` : `Multiple R-squared = 0.2211`  & `Adjusted R-squared = 0.2136`

---
### Point 4
---

**Итог:** каждая из моделей предоставляет практически идентичные другим резултаты. Посмотрим на коэффицинты перед регрессороми в моделях, можно заметить некоторую закономерность. В каждой из построенных моделей коэффициент перед регрессором `age` - количество полных лет - отрицательный. Отсюда можно сделать вывод, что с повышением возраста люди стистически зарабатывают меньше. В каждой из моделей регрессоры `of` - наличие официального трудоустройста, `gov` - принадлежность организации государству, `satisfy` - удослетворенность работой - всегда довольно хорошо связаны с описываемой переменной. Логически это действительно так. Регрессоры `h_educ`, `city_status` так же оказались очень важны. Сравнивая с моделями в которых эти регрессоры выражены не так сильно, можно заметить прирост показателя параметра `Adjusted R-squared` на 1-2%. Как итог получим, что наиболее успешны в плане зарплаты молодые мужчины с высшим образованием  из городов, статистика на противоречит здравому смыслу. 

---
### Point 5
---

Теперь оценим регрессии для предложенных подмножеств:

1. Подмножество 1: Не вступавшие в брак мужчины, без высшего образования
    Уточним датасеты и построим модели: 
    ```R
    data5_1 = subset(ds_2, sex = 1)
    data5_2 = subset(data5_1, wed3 = 1)
    data5_fin = subset(data5_2, h_educ = 0)

    model_5_1 = lm(data = data5_fin, salary ~ log(age) + city_status +
                    log(dur) + I(satisfy^2) + of + gov)
    summary(model_5_1)
    ```

    Вывод:
    ```R
    Coefficients:
             Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -0.96175    0.16832  -5.714 1.53e-08 ***
    log(age)     -0.19842    0.04618  -4.296 1.94e-05 ***
    city_status   0.48497    0.07960   6.093 1.69e-09 ***
    log(dur)      0.17883    0.04057   4.408 1.18e-05 ***
    I(satisfy^2)  0.30497    0.10313   2.957  0.00319 ** 
    of            0.44941    0.11149   4.031 6.06e-05 ***
    gov           0.38369    0.13390   2.865  0.00427 ** 
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1
    Residual standard error: 1.082 on 839 degrees of freedom
    Multiple R-squared:  0.1089,	Adjusted R-squared:  0.1025 
    F-statistic: 17.09 on 6 and 839 DF,  p-value: < 2.2e-16
    ```

    **Итог:** по полученным данным можно предположить, что заработок респондентов огранниченых на `подмножестве 1` сильно зависит от возраста - с увееличением возраста респонденты статистически зарабатывают меньше. Если посмотреть на другие регрессоры, например, на `city_status` & `log_dur`, то можно убедиться что они действительно положительно влияют на описываемую переменную `salary`    

2. Подмножество 2: Городские жители, мужчины состоящие в браке
   Уточним датасеты и построим модели: 
    ```R
    data5_1 = subset(ds_2, sex = 1)
    data5_2 = subset(data5_1, city_status = 1)
    data5_fin = subset(data5_2, wed1 = 1)

    model_5_2 = lm(data = data5_fin, salary ~ log(age) + h_educ +
                    log(dur) + I(satisfy^2) + of + gov)
    summary(model_5_2)
    ```

    Вывод:
    ```R
    Coefficients:
             Estimate Std. Error t value Pr(>|t|)    
    (Intercept)  -0.61121    0.15321  -3.989 7.20e-05 ***
    log(age)     -0.18727    0.04557  -4.110 4.35e-05 ***
    h_educ        0.71432    0.09195   7.769 2.31e-14 ***
    log(dur)      0.16612    0.03971   4.183 3.18e-05 ***
    I(satisfy^2)  0.25840    0.10182   2.538 0.011333 *  
    of            0.40250    0.11037   3.647 0.000282 ***
    gov           0.23492    0.13147   1.787 0.074321 .  
    ---
    Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

    Residual standard error: 1.068 on 839 degrees of freedom
    Multiple R-squared:  0.1319,	Adjusted R-squared:  0.1257 
    F-statistic: 21.25 on 6 and 839 DF,  p-value: < 2.2e-16
    ```

    **Итог:** по полученным данным можно предположить, что заработок респондентов огранниченых на `подмножестве 2` так же сильно зависит от возраста - с увееличением возраста респонденты статистически зарабатывают меньше. Теперь посмотрим на другие регрессоры. Теперь регрессоры `gov` & `I(satisfy^2)` уже не оказывают такое сильное влияние на описываемую переменную, что с одной стороны весьма странно, ведь удовлетворенность работой должна весьма хорошо описывать переменную `salary`, возможно, городское население не так сильно заботится о своей удовлетворенности от работы, закрывая на многое глаза, в пользу высокой зарплаты. Наличие высшего образования и возраст так же сильно положительно и отрицательно соответсвенно влияют на зарплату респондентов.  
    

