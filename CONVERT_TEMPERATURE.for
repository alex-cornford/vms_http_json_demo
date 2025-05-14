!       Example fortran library function to convert temperatures
!
!       Author : Alex Cornford
!       Date   : 24 Jan 2025
!
        REAL*8 FUNCTION CONVERT_TEMPERATURE (IN_SCALE, OUT_SCALE, IN_TEMPERATURE)
        CHARACTER*(*) IN_SCALE, OUT_SCALE
        REAL*8 IN_TEMPERATURE, OUT_TEMPERATURE

        REAL*8 CELSIUS_TEMP

        SELECT CASE (IN_SCALE)
             CASE ('CELSIUS')
                CELSIUS_TEMP = IN_TEMPERATURE
            CASE ('FAHRENHEIT')
                CELSIUS_TEMP = (IN_TEMPERATURE - 32.0) / 9 * 5
            CASE ('KELVIN')
                CELSIUS_TEMP = IN_TEMPERATURE - 273.15
            CASE DEFAULT
                CONVERT_TEMPERATURE = -1000
                RETURN
        END SELECT

        SELECT CASE (OUT_SCALE)
            CASE ('CELSIUS')
                OUT_TEMPERATURE = CELSIUS_TEMP
            CASE ('FAHRENHEIT')
                OUT_TEMPERATURE = (CELSIUS_TEMP * 9 / 5) + 32.0
            CASE ('KELVIN')
                IN_TEMPERATURE = CELSIUS_TEMP + 273.15
            CASE DEFAULT
                OUT_TEMPERATURE = -1000
        END SELECT
        CONVERT_TEMPERATURE = OUT_TEMPERATURE
        RETURN
        END FUNCTION
