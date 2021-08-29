package greetings

import (
	"fmt"
	"errors"
	"math/rand"
	"time"
)

func Hello(name string) (string, error){
	var message string
	var err error

	if name == ""{
		err = errors.New("empty name")
	} else {
		//message = fmt.Sprintf("Hi, %v. Welcome!", name)
		message = fmt.Sprintf(randomFormat(), name)
	}

	//message := fmt.Sprintf("Hi, %v. Welcome!", name)
	return message, err
}

func init(){
	rand.Seed(time.Now().UnixNano())
}

func randomFormat() string {
	formats := []string{
		"Hi, %v. Welcome!",
		"Great to see you, %v!",
		"Hail, %v! Well met!",
		"Hark, %v! Hither thee!",
	}
	return formats[rand.Intn(len(formats))]
}