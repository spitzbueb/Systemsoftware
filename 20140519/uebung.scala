import scala.collection.mutable.HashMap
import scala.collection.immutable.Map
import scala.collection.mutable.Buffer
import scala.collection.immutable.List

object MyMap
{
  def main(args : Array[String]) : Unit = {
    val l : List[String] = List("Erster","Zweiter","Dritter","Vierter")
    println("In Main-Funktion")
    l.foreach { println }
    println("---------------------")
    createMap(l)
  }
  
  def createMap(lst:List[String]) : Unit = {
    println("In Map-Funktion")
    var m : Map[Int,String] = Map()
    var zaehler : Int = 0
    
    for (string <- lst)
    { 
       m += (zaehler -> string)
       zaehler = zaehler+1
    }
    
    
    for ((k,v) <- m) println("key: " + k + " value: " + v)
    println("----------------------")
  }
}