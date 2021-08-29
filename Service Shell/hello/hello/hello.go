package main

import (
	"example.com/greetings"
	"fmt"
	"log"
)

func main(){
	log.SetPrefix("greetings: ")
	log.SetFlags(0)

	names := []string{"Skyler", "Grendel", "Lilly"}

	for _, name := range names{
		message, err := greetings.Hello(name)

		if err != nil {
			log.Fatal(err)
		} else {
			fmt.Println(message)
		}
	}
}