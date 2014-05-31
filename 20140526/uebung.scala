import akka.actor.{Actor, ActorLogging, Props, ActorRef}
import scala.collection.immutable.Map
import scala.collection.mutable.Buffer

class MyMap() extends Actor with ActorLogging {
  import MyMap._
  
  var complaints = 0
  
  override def receive: Receive = {
   case putString(string: String) => {
     for((k,v) <- m) {
      complaints = complaints + 1
     }
     
     m += ((complaints+1) -> string
     
     log.info("String in Map eingefügt")
     sender ! Result("Done")
  }
  
  case getString(x: Int) => {
   sender ! Result(m(x))
  }
    
}

object MyMap
{
    var m : Map[Int,String] = Map()
  
    case class putString(string: String)
    
    case class getString(x: Int)
    
    case class Result(answer: String)
    
    def props(): Props = {
      Props(new MyMap())
    }
}