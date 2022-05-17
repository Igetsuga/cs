library("rlms")
library("dplyr")

library("lmtest")
library("rlms")
library("dplyr")
library("GGally")
library("car")
library("sandwich")

#######################################################################
ds_0 <- rlms_read("r20i_os26c.sav")

ds = select(ds_0, pj13.2, p_age, ph5, p_marst, p_diplom, status, pj6.2, pj1.1.1, pj11.1, pj23)

# исключение строк со значением NA
ds = na.omit(ds)

#######################################################################
# Cемейное положение
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


#######################################################################
# Пол
ds["sex"] = ds$ph5
ds["sex"] = lapply(ds["sex"], as.character)

ds$sex[which(ds$sex == '1')] <- 1
ds$sex[which(ds$sex == '2')] <- 0
ds$sex = as.numeric(ds$sex)

#######################################################################
# Населенный пункт
ds["status1"] = ds$status
ds["status1"] = lapply(ds["status1"], as.character)
ds["city_status"] = 0
ds$city_status[which(ds$status1 == '1')] <- 1
ds$city_status[which(ds$status1 == '2')] <- 1
ds$city_status = as.numeric(ds$city_status)

#######################################################################
# Наличие высшего образования
ds["higher_educ"] = ds$p_diplom
ds["higher_educ"] = lapply(ds["higher_educ"], as.character)
ds["h_educ"] = ds$p_diplom
ds["h_educ"] = 0
ds$h_educ[which(ds$higher_educ == '6')] <- 1

# Образование
# ds["higher_educ"] = ds$s_educ
# ds["higher_educ"] = lapply(ds["higher_educ"], as.character)
# ds["h_educ"] = ds$s_educ
# ds["h_educ"] = 0
# ds$h_educ[which(ds$higher_educ=='21')] <- 1
# ds$h_educ[which(ds$higher_educ=='22')] <- 1
# ds$h_educ[which(ds$higher_educ=='23')] <- 1

#######################################################################
# Зарплата: преобразование в вещественную и нормализация
sal1 = as.character(ds$pj13.2)
sal2 = lapply(sal1, as.integer)
sal = as.numeric(unlist(sal2))

mean(sal)

ds["salary"] = (sal - mean(sal)) / sqrt(var(sal))
ds["salary"]

#######################################################################
# Продолжительность рабочей недели: преобразование в вещественную и нормализация
dur1 = as.character(ds$pj6.2)
dur2 = lapply(dur1, as.integer)
dur3 = as.numeric(unlist(dur2))

mean(dur3)

ds["dur"] = (dur3 - mean(dur3)) / sqrt(var(dur3))
ds["dur"]

#######################################################################
# Возраст: преобразование в вещественную и нормализация
age1 = as.character(ds$p_age)
age2 = lapply(age1, as.integer)
age3 = as.numeric(unlist(age2))

mean(age3)

ds["age"]= (age3 - mean(age3)) / sqrt(var(age3))
ds["age"]

#######################################################################
# Удовлетворенность работой в целом
ds["sat"] = ds$pj1.1.1
ds["sat"] = lapply(ds["sat"], as.character)
ds["satisfy"] = 0
ds$satisfy[which(ds$sat == '1')] <- 1
ds$satisfy[which(ds$sat == '2')] <- 1
ds$satisfy[which(ds$sat == '3')] <- 1
ds$satisfy = as.numeric(ds$satisfy)

#######################################################################
# Официальное трудоустройство
ds["of_w"] = ds$pj1.1.1
ds["of_w"] = lapply(ds["of_w"], as.character)
ds["of"] = 0
ds$of[which(ds$of_w == '1')] <- 1
ds$of = as.numeric(ds$of)

#######################################################################
# Является государство владельцем или совладельцем Вашего предприятия, организации?
ds["gov_1"] = ds$pj11.1
ds["gov_1"] = lapply(ds["gov_1"], as.character)
ds["gov"] = 0
ds$gov[which(ds$gov_1 == '1')] <- 1
ds$gov = as.numeric(ds$gov)

#######################################################################
ds = na.omit(ds)

#######################################################################
# Построение линейной регрессии зависимотсти переменной `salary` от
# всех введеных регрессоров

ds_2 = select(ds, salary, age, sex, h_educ, city_status, dur, wed1, wed2, wed3, satisfy, of, gov)

# модель_1 - `model_def`
model_def = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                 dur + wed1 + wed2 + wed3 + satisfy + of + gov)
summary(model_def)
vif(model_def)

# модель_2 - `model_2`
model_2 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                 dur + wed2 + wed3 + satisfy + of + gov)
summary(model_2)
vif(model_2)

# модель_3 - `model_3`
model_3 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
               dur + wed3 + satisfy + of + gov)
summary(model_3)
vif(model_3)

# модель_4 - `model_4`
model_4 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
               dur + wed3 + satisfy + of + gov)
summary(model_4)
vif(model_4)

# модель_5 - `model_5`
model_5 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
               log(dur) + wed3 + satisfy + of + gov)
summary(model_5)
vif(model_5)

# модель_6 - `model_6`
model_6 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
               log(dur) + wed3 + satisfy + of + gov)
summary(model_6)
vif(model_6)

# модель_7 - `model_7`
model_7 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               log(dur) + wed3 + satisfy + of + gov)
summary(model_7)
vif(model_7)

# модель_8 - `model_8`
model_8 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               I(dur^2) + wed3 + satisfy + of + gov)
summary(model_8)
vif(model_8)

# модель_9 - `model_9`
model_9 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               I(dur^2) + wed3 + I(satisfy^2) + of + gov)
summary(model_9)
vif(model_9)

# модель_10 - `model_10`
model_10 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               log(dur) + wed3 + I(satisfy^2) + of + gov)
summary(model_10)
vif(model_10)

# модель_11 - `model_11`
model_11 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
               log(dur) + wed3 + I(satisfy^2) + of + gov)
summary(model_11)
vif(model_11)

# модель_12 - `model_12`
model_12 = lm(data = ds_2, salary ~ I(age^0.1) + sex + h_educ + city_status +
                dur + I(satisfy^2) + of + gov)
summary(model_12)
vif(model_12)

# модель_13 - `model_13`
model_13 = lm(data = ds_2, salary ~ I(age^0.5) + sex + h_educ + city_status +
                dur + I(satisfy^2) + of + gov)
summary(model_13)
vif(model_13)

# модель_14 - `model_14`
model_14 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                log(dur) + I(satisfy^2) + of + gov)
summary(model_14)
vif(model_14)

# модель_15 - `model_15`
model_15 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                log(dur) + I(satisfy^0.5) + of + gov)
summary(model_15)
vif(model_15)

# модель_16 - `model_16`
model_16 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                log(dur)  + I(satisfy^1.5) + of + gov)
summary(model_16)
vif(model_16)

# модель_17 - `model_17`
model_17 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                log(dur) + I(satisfy^2) + of + gov)
summary(model_17)
vif(model_17)

# модель_18 - `model_18`
model_18 = lm(data = ds_2, salary ~ log(age) + sex + h_educ + city_status +
                I(dur^2) + I(satisfy^2) + of + gov)
summary(model_18)
vif(model_18)

# модель_19 - `model_19`
model_19 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                I(dur^0.1) + satisfy + of + gov)
summary(model_19)
vif(model_19)

# модель_20 - `model_20`
model_20 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
                I(dur^0.5) + satisfy + of + gov)
summary(model_20)
vif(model_20)

# модель_21 - `model_21`
model_21 = lm(data = ds_2, salary ~ I(age^2) + sex + h_educ + city_status +
                I(dur^2) + satisfy + of + gov)
summary(model_21)
vif(model_21)

# модель_22 - `model_22`
model_22 = lm(data = ds_2, salary ~ age + sex + h_educ + city_status +
                log(dur) + satisfy + of + gov)
summary(model_22)
vif(model_22)

#######################################################################


# Не вступавшие в брак мужчины, без высшего образования;

data5_1 = subset(ds_2, sex = 1)
data5_2 = subset(data5_1, wed3 = 1)
data5_fin = subset(data5_2, h_educ = 0)

model_5_1 = lm(data = data5_fin, salary ~ log(age) + city_status +
                 log(dur) + I(satisfy^2) + of + gov)
summary(model_5_1)


#######################################################################

# Городские жители, мужчины состоящие в браке

data5_1 = subset(ds_2, sex = 1)
data5_2 = subset(data5_1, city_status = 1)
data5_fin = subset(data5_2, wed1 = 1)

model_5_2 = lm(data = data5_fin, salary ~ log(age) + h_educ +
                 log(dur) + I(satisfy^2) + of + gov)
summary(model_5_2)


#######################################################################
#######################################################################








